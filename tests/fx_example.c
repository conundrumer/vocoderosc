#include <stdlib.h>
#include <stdio.h>
#include "../src/fx.h"

typedef struct {
    float gain;
} Gain;

void* g_new(float gain) {
    Gain* g = malloc(sizeof(Gain));
    g->gain = gain;
    return (void*)g;
}

float g_process(float input, int i, int bufLength, void* data) {
    // do nothing with these to make the compile shut up
    (void) i;
    (void) bufLength;

    Gain* g = (Gain*) data;
    return g->gain * input;
}

void g_free(void* data) {
    Gain* g = (Gain*) data;
    free(g);
}

int main() {
    // CHANGE: FX_NEW NOW TAKES FXFREE
    Fx* fx = fx_new(g_process, g_free, g_new(0.5));
    float input = 1.0;
    float output = fx_process(fx, input, 0, 1);
    printf("input: %f, output: %f\n", input, output);
    // CHANGE: FX_FREE DOES NOT TAKE FXFREE
    fx_free(fx);
    return 0;
}