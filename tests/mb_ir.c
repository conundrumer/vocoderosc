#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include "../headers/fx_multiband.h"
#include "../headers/utils.h"

#define IR_LEN 1024

int main() {
	int fs = 44100;
	float f_low = 80;
	float f_high = 4000;
	int numBands = 20;
	Fx* fx = fx_new(mb_filter, mb_free, mb_new(f_low, f_high, numBands, fs));
	float impulse = 1.0;
    int i;
    for (i = 0; i < IR_LEN; i++) {
    	if (i != 0) {
    		printf("\t");
    	}
        float output = fx_process(fx, impulse, 0, 1);
        printf("%f", output);
        impulse = 0;
    }
	fx_free(fx);
	return 0;
}
