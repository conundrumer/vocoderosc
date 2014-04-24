#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include "../headers/attenuator.h"

typedef struct {
	float attack;
	float decay;
	float gain;
	float prevGain;
} At;

/**
 * attack: how gradually the gain will increase, if the gain changes
 * decay: how gradually gain will decrease
 */
void* at_new(float attack, float decay) {
	At* at       = malloc(sizeof(At));
	at->attack   = attack;
	at->decay    = decay;
	at->gain     = 1.0;
	at->prevGain = 1.0;
	return (void*) at;
}

/**
 * attentuates gradually, from start of the buffer to 
 * end of buffer from previous gain to current gain, with some
 * adjustments from attack/decay
 */
float at_filter(float input, int i, int buflength, void* data) {
	At* at = (At*) data;
	float slope = (at->gain - at->prevGain)/buflength;
	if (slope < 0.0) {
		input = (at->decay * slope * input * i) + at->prevGain;
	} else {
		input = (at->attack * slope * input * i) + at->prevGain;
	}
	return input;
}

/* changes the gain of the attenuator */
void at_setGain(float gain, void* data) {
	At* at       = (At*) data;
	at->prevGain = at->gain;
	at->gain     = gain;
}

void at_free(void* data) {
	At* at = (At*) data;
	free(at);  
}
