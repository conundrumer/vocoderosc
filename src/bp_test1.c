#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include "fx.h"
#include "bandpass.h"

int main() {
    Fx* fx = fx_new(bp_filter, bp_new(1.0/6.0, 0.066*2.0, 1));
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
        float input = sin(M_PI/3.0*(float)i);
        float output = fx_process(fx, input, 0, 1);
        if (i > 290) {
            printf("%f\t%f\n", input, output);
        }
    }

    printf("Testing band edge...\n");
    for (i = 0; i < 300; i++) {
        float input = sin(M_PI*(1.0/3.0+0.066)*(float)i);
        float output = fx_process(fx, input, 0, 1);
        if (i > 290) {
            printf("%f\t%f\n", input, output);
        }
    }
    fx_free(fx, bp_free);
    return 0;
}