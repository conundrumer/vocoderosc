#pragma once

#include "fx.h"

// frequency range from f_low to f_high
// in numBands bands of constant q
// ie logarithmically spaced
void* vcc_new(float f_low, float f_high, int numBands, int fs);

float vcc_filter(float input, int i, int bufLength, void* data);

void vcc_free(void* data);

// vcc will use the volume at this pointer to set band volumes
void vcc_setBandVolumePointer(int band, float* volume, void* data);
