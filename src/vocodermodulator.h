#pragma once

#include "fx.h"
#include "volumedetector.h"
#include "fx_multiband.h"

void* vcm_new(float f_low, float f_high, int numBands, int fs,
	VdCallback bandVolumeCallback, void* callbackparams);

float vcm_filter(float input, int i, int bufLength, void* data);

void vcm_free(void* data);
