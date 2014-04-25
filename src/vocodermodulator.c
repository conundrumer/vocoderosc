#include <stdlib.h>
#include "../headers/vocodermodulator.h"
#include "../headers/fx.h"
#include "../headers/volumedetector.h"
#include "../headers/fx_multiband.h"

typedef struct {
    int numBands;
    float** vdVols;
    Fx* mb;
} Vcm;

void* vcm_new(float f_low, float f_high, int numBands, int fs) {
    Vcm* vcm       = malloc(sizeof(Vcm));
    vcm->vdVols    = malloc(numBands*sizeof(float*));
    vcm->numBands  = numBands;
    void* mb       = mb_new(f_low, f_high, numBands, fs);
    vcm->mb        = fx_new(mb_filter, mb_free, mb);
    int b;
    for (b = 0; b < numBands; b++) {
        void* rawVd = vd_new();
        mb_addFx(fx_new(vd_findVolume, vd_free, rawVd), b, mb);
        vcm->vdVols[b] = vd_getVolumePointer(rawVd);
    }
    return (void*) vcm;
}

float vcm_filter(float input, int i, int bufLength, void* data) {
    Vcm* vcm = (Vcm*) data;
    return fx_process(vcm->mb, input, i, bufLength);
}

void vcm_free(void* data) {
    Vcm* vcm = (Vcm*) data;
    fx_free(vcm->mb);
    int i;
    for (i = 0; i < vcm->numBands; i++) {
        free(vcm->vdVols[i]);
    }
    free(vcm->vdVols);
    free(vcm);
}

float* vcm_getBandVolumePointer(int band, void* data) {
    Vcm* vcm = (Vcm*) data;
    return vcm->vdVols[band];
}
