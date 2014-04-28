#include <stdlib.h>
#include <stdio.h>
#include "../headers/vocodercarrier.h"
#include "../headers/attenuator.h"

int main() {
	int fs        = 20;
	float f_low   = 1.0;
	float f_high  = 8.0;
    int numBands  = 20;
    void* vcc     = vcc_new(f_low, f_high, numBands, fs);
    Fx* fx        = fx_new(vcc_filter, vcc_free, vcc);
    float impulse = 1.0;
    int bufLength = 4;
    int i;
    int b;

    for (b = 0; b < numBands; b++) {
        float* volume= malloc(sizeof(float));
        *volume = 1.0;
        if (b == numBands/2) {
            // *volume = 0.0;
        }
        vcc_setBandVolumePointer(b, volume, vcc);
    }
    float output;
    printf("Testing impulse response...\n");
    // for (b = 0; b < 4; b++) {
        for (i = 0; i < bufLength; i++) {
            output = fx_process(fx, 0.0, i, bufLength);
            printf("%f\n", output);
            // if (b != 9) {
            //     output = fx_process(fx, 0.0, i, bufLength);
            // }
            // else {
            //     output = fx_process(fx, impulse, i, bufLength);
            //     impulse = 0;
                
            // }
        }
    // }
	fx_free(fx);
	return 0;
}