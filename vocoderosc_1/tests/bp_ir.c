#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include "../headers/fx.h"
#include "../headers/bandpass.h"
#include "../headers/utils.h"

#define NUM_FREQS 8
#define NUM_BW 1
#define IR_LEN 256

void printIR(float freq, float bw, int fs, int ir_length) {
    Fx* fx = fx_new(bp_filter, bp_free, bp_new(freq, bw, fs));
    float impulse = 1.0;
    int i;
    for (i = 0; i < ir_length; i++) {
        if (i != 0) {
            printf("\t");
        }
        float output = fx_process(fx, impulse, 0, 1);
        printf("%f", output);
        impulse = 0;
    }
    fx_free(fx);
}

int main() {
    int fs = 2;
    float freq;
    float bw;
    int b, f;
    for (f = 1; f <= NUM_FREQS; f++) {
        freq = ((float) f) / (NUM_FREQS+1) * fs/2;
        for (b = 1; b <= NUM_BW; b++) {
            bw = ((float) b) / (NUM_BW) * fs/2 / (NUM_FREQS+1);
            // printf("freq: %f, bw: %f\n", freq, bw);
            printIR(freq, bw, fs, IR_LEN);
            printf("\n");
        }
    }
    return 0;
}
