#pragma once
#include <stdlib.h>
#include <math.h>
#include "fx.h"

// frequency range from f_low to f_high
// in numBands bands of constant q
// ie logarithmically spaced
void* mb_new(float f_low, float f_high, int numBands, int fs);

float mb_filter(float input, int i, int bufLength, void* data);

void mb_free(void* data);

// band is the index of the band, from low 0 to numBands
void mb_addFx(Fx* fx, int band);