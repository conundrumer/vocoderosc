#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include "../headers/vocodermodulator.h"
#include "../headers/bandvolume.h"

void vd_callback (float volume, void* data) {
	BandVolume* bv = (BandVolume*) data;
	printf("%i: %f\n", bv->band, volume);
}

int main() {
	int fs       = 20;
	float f_low  = 2.0;
	float f_high = 8.0;
	int numBands = 10;
	Fx* fx       = fx_new(vcm_filter, vcm_free, vcm_new(f_low, f_high, numBands,
						  fs, vd_callback, NULL));
	float impulse = 1.0;
    int bufLength = 32;
    int i;
    
    printf("Testing impulse response...\n");
    for (i = 0; i < bufLength+1; i++) {
        fx_process(fx, impulse, i, bufLength);
        impulse = 0;
    }
	fx_free(fx);
	return 0;
}
