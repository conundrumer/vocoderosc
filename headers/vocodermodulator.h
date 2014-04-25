#pragma once

#include "fx.h"
#include "volumedetector.h"

void* vcm_new(float f_low, float f_high, int numBands, int fs);

float vcm_filter(float input, int i, int bufLength, void* data);

void vcm_free(void* data);

// pointer to the volume of a band, vcm will malloc and free
float* vcm_getBandVolumePointer(int band, void* data);
