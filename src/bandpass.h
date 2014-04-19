#pragma once

/* freq in hz */
void* bp_new(float freq, float q);

/* outputs a bandpass filtered sample based on input and previous
 * inputs/outputs */
float bp_filter(float input, int i, int bufLength, void* data);

void bp_free(void* data);
