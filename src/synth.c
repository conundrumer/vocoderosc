#include <stdlib.h>
#include <stdio.h>
#include "synth.h"

Synth* synth_new(int fs, int numvoices) {
	Synth* synth = malloc(sizeof(Synth*));
	synth->poly = numvoices;
	synth->saws = malloc(numvoices*sizeof(Saw*));
	int i;
	for (i = 0; i < numvoices; i++) {
		Saw* s_i = saw_new(fs);
		synth->saws[i] = s_i;
	}
	return synth;
}

void synth_on(int key, Synth* s) {
	Saw** saws = s->saws;
	int i;
	for (i = 0; i < s->poly; i++) {
		if (check_key(-1,saws[i])) { // this saw is not active
			saw_on(key, saws[i]);
			printf("key: %d\nsaw: %d\n", key, i);
			return;
		}
	}
}

void synth_off(int key, Synth* s) {
	Saw** saws = s->saws;
	int i;
	for (i = 0; i < s->poly; i++) {
		if (check_key(key, saws[i])) {
			saw_off(saws[i]);
			printf("synth_off: key = %d\nsaw: %d\n\n", key,i);
			return;
		}
	}
}

void synth_free(Synth* s) {
	free(s);
}

float* synth_getBuffer(int bufLength, Synth* s) {
	// int sum = 0;
	int i, j;
	Saw** saws = s-> saws;
	float* outputBuffer = malloc(bufLength*sizeof(float));
	for (i = 0; i < bufLength; i++) {
		float sample = 0.0;
		for (j = 0; j < s->poly; j++) {
			if (saws[j]->key > -1) {
				sample += saws[j]->phase;
				saws[j]->phase += 1.0/(20.0*saws[j]->period);
				// Drop to -1.0 when signal reaches 1.0
				if (saws[j]->phase >= 1.0f) saws[j]->phase = -1.0f;
			}
		}
		outputBuffer[i] = sample;
	}
	return outputBuffer;
}
