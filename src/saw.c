#include <stdlib.h>
#include <stdio.h>
#include "saw.h"
#include "utils.h"
#include <math.h>

#define F0 (100.0)
#define K0 (1)
#define NUM_KEYS (12)

Saw* saw_new(int fs) {
	Saw* saw = malloc(sizeof(Saw));
	saw->fs = fs;
	saw->key = -1;
	saw->currentSample = 0.0;
	return saw;
}

int check_key(int key, Saw* saw) {
	return (key == saw->key);
}

void saw_on(int key, Saw* saw) {
	saw->key = key;
}

void saw_off(Saw* saw) {
	saw->key = -1;
	saw->currentSample = 0.0;
}

float saw_getNext(Saw* saw) {
	if (saw->key > -1) {
		// float period = (saw->fs)/(F0*powf(2.0,((float)(saw->key)-K0)/NUM_KEYS));
		float period = getPeriod(saw->fs, saw->key, F0, K0, NUM_KEYS);
		float slope = 2.0/period;
		saw->currentSample += slope;
		// Drop to -1.0 when signal reaches 1.0
		if (saw->currentSample > 1.0f) {
			saw->currentSample -= 2.0f;
		}
		return saw->currentSample;
	}
	return saw->currentSample;
}

void saw_free(Saw* saw) {
	free(saw);
}

// int main(void) {
// 	Saw* s = saw_new(44100);
// 	printf("%f\n",saw_getNext(s));
// 	saw_free(s);
// 	return 0;
// }