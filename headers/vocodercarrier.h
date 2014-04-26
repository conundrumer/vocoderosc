#pragma once
#include "fx.h"

/**
 * Vcc:
 * Contains a multiband Fx, an array of pointers to band volumes, the
 * number of bands, and an array of raw attenuators for setting their gains.
 */
typedef struct {
    int     numBands;
    void**  ats;
    float** vols;
    Fx*     mb;
} Vcc;

/**
 * vcc_new: 
 * Initializes a new multiband containing attenuators and bandpass filters
 * for each band. Also sets band volume pointers and the array of ats.
 * Frequencies range from f_low to f_high in numBands bands of constant q
 * (i.e. logarithmically spaced).
 */
void* vcc_new(float f_low, float f_high, int numBands, int fs);

/**
 * vcc_filter: Applies bandpass filters and then attenuates synthesizer
 *             samples using gains from the previous buffer. Then sets
 *             attenuator gains to values updated in vcm_filter.
 */
float vcc_filter(float input, int i, int bufLength, void* data);

/* vcc_free: Frees the multiband, volume pointers, attenuators, and the vcc */
void vcc_free(void* data);

/**
 * vcc_setBandVolumePointer:
 * Vcc will use the volume at this pointer to set band volumes.
 */
void vcc_setBandVolumePointer(int band, float* volume, void* data);
