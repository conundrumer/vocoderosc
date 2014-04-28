#pragma once

#include "fx.h"
#include "volumedetector.h"

/**
 * Vcm:
 * Contains a multiband Fx, an array of pointers to band volumes, and the
 * number of bands.
 */
typedef struct {
    int numBands;
    float** vdVols;
    Fx* mb;
} Vcm;

/**
 * vcm_new: 
 * Initializes a new multiband containing volume detectors and bandpass filters
 * for each band. Also sets band volume pointers.
 */
void* vcm_new(float f_low, float f_high, int numBands, int fs);

/**
 * vcm_filter: 
 * Applies bandpass filters and volume detectors. Sets volume pointers for
 * each band. 
 */
float vcm_filter(float input, int i, int bufLength, void* data);

/* vcm_free: Frees the volume detectors, the multiband, and vcm struct. */
void vcm_free(void* data);

/* vcm_getBandVolumePointer:
 * Returns a pointer to the volume of a band, vcm will malloc and free.
 */
float* vcm_getBandVolumePointer(int band, void* data);
