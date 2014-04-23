#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include "fx_multiband.h"
#include "utils.h"

int main() {
	int fs = 20;
	float f_low = 2.0;
	float f_high = 8.0;
	int numBands = 10;
	Fx* fx = fx_new(mb_filter, mb_free, mb_new(f_low, f_high, numBands, fs));
	float impulse = 1.0;
    int i;
    printf("Impulse response:\n");
    for (i = 0; i < 32; i++) {
        float output = fx_process(fx, impulse, 0, 1);
        printf("%f\n", output);
        impulse = 0;
    }
	fx_free(fx);
	return 0;
}
