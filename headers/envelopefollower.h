#pragma once

// TODO: make attack and decay consistent
// attack: how gradually envelope will increase
// decay: how gradually envelope will decrease
void* ef_new(float attack, float decay);

// returns a sample to the envelope following the signal
float ef_filter(float input, int i, bufLength, void* data);

void ef_free(void* data);