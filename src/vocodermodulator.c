/**
 * Vcm:
 * Contains a multiband Fx, an array of pointers to band volumes, and the
 * number of bands.
 */

#include <stdlib.h>
#include "../headers/vocodermodulator.h"
#include "../headers/fx.h"
#include "../headers/volumedetector.h"
#include "../headers/fx_multiband.h"

/**
 * vcm_new: 
 * Initializes a new multiband containing volume detectors and bandpass filters
 * for each band. Also sets band volume pointers.
 */
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

/**
 * vcm_filter: 
 * Applies bandpass filters and volume detectors. Sets volume pointers for
 * each band. 
 */
float vcm_filter(float input, int i, int bufLength, void* data) {
    Vcm* vcm = (Vcm*) data;
    return fx_process(vcm->mb, input, i, bufLength);
}

/* vcm_free: Frees the volume detectors, the multiband, and vcm struct. */
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

/* vcm_getBandVolumePointer:
 * Returns a pointer to the volume of a band, vcm will malloc and free.
 */
float* vcm_getBandVolumePointer(int band, void* data) {
    Vcm* vcm = (Vcm*) data;
    return vcm->vdVols[band];
}
