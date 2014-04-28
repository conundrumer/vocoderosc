#pragma once

// threshold: the (linear) volume where, if the input amplitude exceeds this,
// the output volume gets reduced to this volume
// gain: how much to increase the volume after thresholding
// attack: how gradually to reduce volume after volume is past threshold
// decay: how gradually to restore volume after volume is below theshold
void* lm_new(float threshold, float gain, float attack, float decay);

float lm_filter(float input, int i, int bufLength, void* data);

void lm_free(void* data);