#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include "../headers/vocodermodulator.h"

int main() {
	int fs       = 20;
	float f_low  = 2.0;
	float f_high = 8.0;
	int numBands = 10;
	Fx* fx       = fx_new(vcm_filter, vcm_free, vcm_new(f_low, f_high, numBands,
						  fs));
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
