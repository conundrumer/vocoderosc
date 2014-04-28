#include <stdlib.h>
#include "../headers/vocodercarrier.h"
#include "../headers/attenuator.h"
#include "../headers/fx_multiband.h"

/**
 * vcc_new: 
 * Initializes a new multiband containing attenuators and bandpass filters
 * for each band. Also sets band volume pointers and the array of ats.
 * Frequencies range from f_low to f_high in numBands bands of constant q
 * (i.e. logarithmically spaced).
 */
void* vcc_new(float f_low, float f_high, int numBands, int fs) {
    int i;
    Vcc* vcc     = malloc(sizeof(Vcc));
    void** ats   = malloc(numBands*sizeof(void*));
    float** vols = malloc(numBands*sizeof(float*));
    void* rawMb  = mb_new(f_low, f_high, numBands, fs);
    Fx* mb       = fx_new(mb_filter, mb_free, rawMb);
    for (i = 0; i < numBands; i++) {
        void* rawAt = at_new(0.0, 0.0);
        ats[i]      = rawAt;
        vols[i]     = malloc(sizeof(float));
        *(vols[i])  = 0.0;
        mb_addFx(fx_new(at_filter, at_free, rawAt), i, rawMb);
    }
    vcc->numBands = numBands;
    vcc->vols     = vols;
    vcc->ats      = ats;
    vcc->mb       = mb;
    return (void*) vcc;
}

/**
 * vcc_filter: Applies bandpass filters and then attenuates synthesizer
 *             samples using gains from the previous buffer. Then sets
 *             attenuator gains to values updated in vcm_filter.
 */
float vcc_filter(float input, int i, int bufLength, void* data) {
    (void) i;
    int b;
    Vcc* vcc = (Vcc*) data;
    // This line will apply the bp_filter and then at_filter to the sample
    float output = fx_process(vcc->mb, input, i, bufLength);
    // Set the gain for each band at the end of the buffer.
    // The new gain is *(vcc->vols[b]) and has been set previously within
    //     the call to vcm_filter that came before this function call.
    if (i == bufLength - 1) {
        for (b = 0; b < vcc->numBands; b++) {
            float bandVolume = *(vcc->vols[b]);
            at_setGain(bandVolume,vcc->ats[b]);
        }
    }
    return output;
}

/* vcc_free: Frees the multiband, volume pointers, attenuators, and the vcc */
void vcc_free(void* data) {
    Vcc* vcc = (Vcc*) data;
    fx_free(vcc->mb);
    int i;
    for (i = 0; i < vcc->numBands; i++) {
        free(vcc->vols[i]);
        at_free(vcc->ats[i]);
    }
    free(vcc->vols);
    free(vcc->ats);
    free(vcc);
}

/**
 * vcc_setBandVolumePointer:
 * Vcc will use the volume at this pointer to set band volumes.
 */
void vcc_setBandVolumePointer(int band, float* volume, void* data) {
    Vcc* vcc = (Vcc*) (data);
    vcc->vols[band] = volume;

}
