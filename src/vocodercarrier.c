#include <stdlib.h>
#include "../headers/vocodercarrier.h"
#include "../headers/attenuator.h"
#include "../headers/fx_multiband.h"

typedef struct {
    int     numBands;
    void**  ats;
    float** vols;
    Fx*     mb;
} Vcc;

// Frequency ranges from f_low to f_high in numBands bands of constant q
// (i.e. logarithmically spaced)
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

// Sets the gain for a band's attenuator to the input volume
float vcc_filter(float input, int i, int bufLength, void* data) {
    (void) i;
    int b;
    Vcc* vcc = (Vcc*) data;
    // Set the gain for each band
    for (b = 0; b < vcc->numBands; b++) {
        void* at = vcc->ats[b];
        if (b == 0) {
            at_setGain(0.0, *(vcc->vols[b]),at);
        }
        else {
            at_setGain(*(vcc->vols[b-1]), *(vcc->vols[b]), at);
        }
    }
    return fx_process(vcc->mb, input, i, bufLength);
}

void vcc_free(void* data) {
    Vcc* vcc = (Vcc*) data;
    fx_free(vcc->mb);
    free(vcc->vols);
    free(vcc->ats);
    free(vcc);
}

void vcc_setBandVolumePointer(int band, float* volume, void* data) {
    Vcc* vcc = (Vcc*) (data);
    vcc->vols[band] = volume;
}
