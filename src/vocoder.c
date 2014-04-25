#include <stdlib.h>
#include "../headers/vocoder.h"
#include "../headers/vocodercarrier.h"
#include "../headers/vocodermodulator.h"

Vocoder* vc_new(float f_low, float f_high, int numBands, int fs) {
    Vocoder* vc = malloc(sizeof(Vocoder));
    void* vcc   = vcc_new(f_low, f_high, numBands, fs);
    void* vcm   = vcm_new(f_low, f_high, numBands, fs);
    vc->vcc     = fx_new(vcc_filter, vcc_free, vcc);
    vc->vcm     = fx_new(vcm_filter, vcm_free, vcm);
    int b;
    for (b = 0; b < numBands; b++) {
        float* v = vcm_getBandVolumePointer(b, vcm);
        vcc_setBandVolumePointer(b, v, vcc);
    }
    return vc;
}

float vc_process(float input_m, float input_c, int i, int bufLength, Vocoder* vc) {
    fx_process(vc->vcm, input_m, i, bufLength); // what is being done with mb_out?
    float result = fx_process(vc->vcc, input_c, i, bufLength);
    return result;
}

void vc_free(Vocoder* vc) {
    fx_free(vc->vcm);
    fx_free(vc->vcc);
    free(vc);
}