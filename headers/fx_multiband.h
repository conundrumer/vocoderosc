#pragma once

#include "fx.h"

/**
 * mb_new:
 * Mallocs an array of bandpass filters and Fx's and initializes each one.
 */
void* mb_new(float f_low, float f_high, int numBands, int fs);

// mb_filter: Applies each bandpass filter and uses the output to apply the Fx.
float mb_filter(float input, int i, int bufLength, void* data);

// mb_free: Frees each bandpass filter and Fx.
void mb_free(void* data);

// mb_addFx: Adds a new to the the array of Fx's using band as the index.
void mb_addFx(Fx* fx, int band, void* data);