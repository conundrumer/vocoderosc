#pragma once

void* pd_new();

// returns the maximum absolute value of a buffer
float pd_filter(float input, int i, int bufLength, void* data);

void pd_free(void* data);