#pragma once
#include "fx.h"

typedef struct {
    Fx* vcm;
    Fx* vcc;
} Vocoder;

Vocoder* vc_new(float f_low, float f_high, int numBands, int fs);

float vc_process(float input_m, float input_c, int i, int bufLength, Vocoder* vc);

void vc_free(Vocoder* vc);