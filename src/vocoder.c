#include <stdlib.h>
#include "../headers/vocoder.h"
#include "../headers/vocodercarrier.h"
#include "../headers/vocodermodulator.h"

/**
 * vc_new: 
 * Initializes new vcc and vcm Fx's and allocates memory for a new Vocoder.
 * vcc band volume pointers point to vcm band volume pointers.
 */
Vocoder* vc_new(float f_low, float f_high, int numBands, int fs) {
    Vocoder* vc = malloc(sizeof(Vocoder));
    void* vcc   = vcc_new(f_low, f_high, numBands, fs);
    void* vcm   = vcm_new(f_low, f_high, numBands, fs);
    vc->vcc     = fx_new(vcc_filter, vcc_free, vcc);
    vc->vcm     = fx_new(vcm_filter, vcm_free, vcm);
    int b;
    for (b = 0; b < numBands; b++) {
        float* v = vcm_getBandVolumePointer(b, vcm);
        vcc_setBandVolumePointer(b, v, vcc); // sets the carrier volume ptrs
    }
    return vc;
}

/**
 * vc_process: Does the following in order
 * 1. vcm_filter: Applies bandpass filters and volume detectors. Sets
 *                volume pointers for each band. 
 * 2. vcc_filter: Applies bandpass filters and then attenuates synthesizer
 *                samples using gains from the previous buffer. Then sets
 *                attenuator gains to values updated in vcm_filter.
 */
float vc_process(float input_m, float input_c, int i, int bufLength, Vocoder* vc) {
    fx_process(vc->vcm, input_m, i, bufLength);
    float result = fx_process(vc->vcc, input_c, i, bufLength);
    return result;
}

/* vc_free: Frees the vcm, vcc, and finally the vocoder struct. whee */
void vc_free(Vocoder* vc) {
    fx_free(vc->vcm);
    fx_free(vc->vcc);
    free(vc);
}