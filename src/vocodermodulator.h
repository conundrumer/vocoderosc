#pragma once

#include "fx.h"
#include "volumedetector.h"

void* vcm_new(float f_low, float f_high, int numBands, int fs, VdCallback bandVolumeCallback);

float vcm_filter(float input, int i, int bufLength, void* data);

void vcm_free(void* data);
