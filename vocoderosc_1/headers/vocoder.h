#pragma once
#include "fx.h"

/**
 * Vocoder:
 * Contains the modulator Fx and carrier Fx to apply to samples from the
 * mic input and the synthesizer.
 */
typedef struct {
    Fx* vcm; // Modulator (mic input)
    Fx* vcc; // Carrier (synthesizer)
} Vocoder;

/**
 * vc_new: 
 * Initializes new vcc and vcm Fx's and allocates memory for a new Vocoder.
 * vcc band volume pointers point to vcm band volume pointers.
 */
Vocoder* vc_new(float f_low, float f_high, int numBands, int fs);

/**
 * vc_process: Does the following in order
 * 1. vcm_filter: Applies bandpass filters and volume detectors. Sets
 *                volume pointers for each band. 
 * 2. vcc_filter: Applies bandpass filters and then attenuates synthesizer
 *                samples using gains from the previous buffer. Then sets
 *                attenuator gains to values updated in vcm_filter.
 */
float vc_process(float input_m, float input_c, int i, int bufLength, Vocoder* vc);

/* vc_free: Frees the vcm, vcc, and finally the vocoder struct. whee */
void vc_free(Vocoder* vc);