#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include "attenuator.h"
// #define M_PI (3.14159265)

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
	return input;
}

void at_free(void* data) {
	At* at = (At*) data;
	free(at);  
}

/* changes the gain of the attenuator */
void at_setGain(float gain, void* data) {
	At* at = (At*) data;
	at->prevGain = at->gain;
	at->gain = gain;
}

// int main() {
// 	int buflength = 25;
// 	int i;
// 	float prev = 0.0;
// 	float x;
// 	float* sintable = malloc(buflength*sizeof(float));
// 	// printf("\n................................\ni\tx\t\tsin(x)\n................................\n");
// 	for (i = 0; i < buflength; i++) {
// 		x = 3*M_PI*((float)i/buflength);
// 		prev = sin(x);
// 		sintable[i]=prev;
// 		// printf("%d\t%f\t%f\n",i,x,sintable[i]);
// 	}
// 	float* ones = malloc(buflength*sizeof(float));
// 	for (i = 0; i < buflength; i++) {
// 		ones[i] =1.0;
// 	}
// 	At* at = at_new(1.0, 1.0);
// 	at_setGain(8.0,(void*)at);
// 	float filtered;
// 	printf("\ngain = 8.0\n......................................\ni\torig\t\tnew\n......................................\n");
// 	for (i = 0; i < buflength; i++) {
// 		filtered = at_filter(ones[i], i, buflength, at);
// 		// filtered = at_filter(sintable[i],i,buflength,at);
// 		// printf("%d\t%f\t%f\n",i,sintable[i],filtered);
// 		printf("%d\t%f\t%f\n",i,ones[i],filtered);

// 	}
// 	return 0;
// }
