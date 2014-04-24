#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include "../src/fx.h"
#include "../src/bandpass.h"
#include "../src/utils.h"

int main() {
    int fs = 4;
    float freq = 1.0;
    float bw = 0.2;
    Fx* fx = fx_new(bp_filter, bp_free, bp_new(freq, bw, fs));
    float impulse = 1.0;
    int i;
    printf("Testing impulse response...\n");
    for (i = 0; i < 10; i++) {
        float output = fx_process(fx, impulse, 0, 1);
        printf("%d: %f\n", i, output);
        impulse = 0;
    }
    printf("Testing resonance...\n");
    for (i = 0; i < 300; i++) {
        float input = sin(freqtoang(freq,fs)*(float)i);
        float output = fx_process(fx, input, 0, 1);
        if (i > 290) {
            printf("%f\t%f\n", input, output);
        }
    }

    printf("Testing band edge...\n");
    for (i = 0; i < 300; i++) {
        float input = sin(freqtoang(freq+bw/2.0,fs)*(float)i);
        float output = fx_process(fx, input, 0, 1);
        if (i > 290) {
            printf("%f\t%f\n", input, output);
        }
    }
    fx_free(fx);
    return 0;
}