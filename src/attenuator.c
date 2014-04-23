#include <stdlib.h>
#include "attenuator.h"

typedef struct {
	float attack;
	float decay;
	float gain;
	float prevGain;
} At;

/*
 * attack: how gradually the gain will increase, if the gain changes
 * decay: how gradually gain will decrease
 */
void* at_new(float attack, float decay) {
	At* at = malloc(sizeof(At));
	at->attack = attack;
	at->decay = decay;
	at->gain = 1.0;
	at->prevGain = 1.0;
	return (void*)at;
}

/*
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
	at->prevGain = at->gain;
	return input;
}

void at_free(void* data) {
	At* at = (At*) data;
	free(at);
}

/* changes the gain of the attenuator */
void at_gain(float gain, void* data) {
	At* at = (At*) data;
	at->gain = gain;
}

int main() {
	At* at = at_new(0.25, 0.75);
	at_gain(8.0,(void*)at);
	float newSample = at_filter(0.2, 4, 20, (void*)at);
	printf("before: 0.2\n after: %f\n", newSample);
	return 0;
}