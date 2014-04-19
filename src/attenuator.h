#pragma once

/* attack: how gradually gain will increase, if the gain changes
 * decay: how gradually gain will decrease */
void* at_new(float attack, float decay);

/**
 * at_filter: attenuates gradually, from start of the buffer to the end of
 * buffer from previous gain to current gain, with some adjustments from
 * attack/decay
 */
float at_filter(float input, int i, int bufLength, void* data);

void at_free(void* data);

/* changes the gain of the attenuator */
void at_gain(float gain, void* data);
