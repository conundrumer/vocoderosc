#include <stdlib.h>
#include <stdio.h>
#include "../headers/vocodercarrier.h"
#include "../headers/bandvolume.h"
#include "../headers/attenuator.h"

int main() {
	int fs        = 20;
	float f_low   = 2.0;
	float f_high  = 8.0;
    int numBands  = 10;
    void* vcc     = vcc_new(f_low, f_high, numBands, fs);
    Fx* fx        = fx_new(vcc_filter, vcc_free, vcc);
    float impulse = 1.0;
    int bufLength = 32;
    int i;

    BandVolume* bv = malloc(sizeof(BandVolume));
    bv->band = 5;
    bv->data = vcc;
    
    printf("Testing impulse response...\n");
   	// vcc_setBandVolume(0.1, bv);
    for (i = 0; i < bufLength+1; i++) {
        float output = fx_process(fx, impulse, i, bufLength);
        impulse = 0;
		printf("%i: %f\n", i, output);
    }
	fx_free(fx);
	return 0;
}