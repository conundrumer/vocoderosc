#pragma once

#include "fx.h"
#include "volumedetector.h"
#include "fx_multiband.h"

typedef struct {
	float f_low;
	float f_high;
	int numBands; 
	int fs; 
	VdCallback bandVolumeCallback;
	Fx* mb;
} Vcm;

void* vcm_new(float f_low, float f_high, int numBands, int fs, VdCallback bandVolumeCallback) {
	Vcm* vcm = malloc(sizeof(Vcm));
	vcm->f_low = f_low;
	vcm->f_high = f_high;
	vcm->numBands = numBands;
	vcm->fs = fs;
	vcm->bandVolumeCallback = bandVolumeCallback;
	Fx* mb = fx_new(mb_filter, mb_free, mb_new(f_low, f_high, numBands, fs));
	for (int i = 0; i < numBands; i++) {
		int* band = malloc(sizeof(int));
		*band = i;
		Fx* vd = fx_new(vd_findVolume, vd_free, vd_new(bandVolumeCallback, (void*) band));
		mb_addFx(mb, i);
	}
	vcm->mb = mb;
	return (void*)vcm;
}

float vcm_filter(float input, int i, int bufLength, void* data) {

}

void vcm_free(void* data) {
	(Vcm*) vcm = (Vcm*) data;
	free(vcm);
}
