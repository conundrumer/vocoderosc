#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include "../headers/vocoder.h"

int main() {

	int fs = 10;
	int numBands = 3;
	int bufLength = 8;

	Vocoder* vc = vc_new(1, 3, numBands, fs);
	int i, j;
	// printf("modulator\tcarrier\tout\n");
	for (i = 0; i < 3; i++) {
		for (j = 0; j < bufLength; j++) {
			float input_m = 1.0*sin(2*M_PI*2/fs*j);
			float input_c = 2.0*(float)rand()/(float)RAND_MAX - 1.0;
			float output = vc_process(input_m, input_c, j, bufLength, vc);
			if (i < 100) {
				// printf("%f\t%f\t%f\n", input_m, input_c, output);
			}
		}
	}

	vc_free(vc);

	return 0;
}