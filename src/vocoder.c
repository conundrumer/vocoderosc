#include <stdlib.c>
#include "vocoder.h"

Vocoder* vc_new(float f_low, float f_high, int numBands, int fs) {
	Vocoder* vc = malloc(sizeof(Vocoder));
	void* vcc = vcc_new(f_low, f_high, numBands, fs);
	void* vcm = vcm_new(f_low, f_high, numBands, fs, vcc_setBandVolume, vcc);
	vc->vcc = fx_new(vcc_filter, vcc_free, vcc);
	vc->vcm = fx_new(vcm_filter, vcm_free, vcm);
	return vc;
}

float vc_process(float input_m, float input_c, int i, int bufLength, Vocoder* vc) {
	fx_process(input_m, i, bufLength, vc->vcm);
	return fx_process(input_c, i, bufLength, vc->vcc);
}

void vc_free(Vocoder* vc) {
	fx_free(vc->vcm);
	fx_free(vc->vcc);
	free(vc);
}