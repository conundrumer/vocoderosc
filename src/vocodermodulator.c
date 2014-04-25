#include <stdlib.h>
#include "../headers/vocodermodulator.h"
#include "../headers/fx.h"
#include "../headers/volumedetector.h"
#include "../headers/fx_multiband.h"

typedef struct {
    int numBands;
    Fx* mb;
} Vcm;

void* vcm_new(float f_low, float f_high, int numBands, int fs) {
    Vcm* vcm      = malloc(sizeof(Vcm));
    vcm->numBands = numBands;
    void* mb      = mb_new(f_low, f_high, numBands, fs);
    vcm->mb       = fx_new(mb_filter, mb_free, mb);
    int b;
    for (b = 0; b < numBands; b++) {
        Fx* vd = fx_new(vd_findVolume, vd_free, vd_new());
        mb_addFx(vd, b, mb);
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
    free(vcm);
}

float* vcm_getBandVolumePointer(int band, void* data) {
    Vcm* vcm = (Vcm*) data;
    Fx* bp = vcm->mb->bands[band]; // Get the band

}
