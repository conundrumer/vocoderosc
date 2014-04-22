#include <stdlib.h>
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
		}
	}
}

void synth_off(int key, Synth* s) {
	Saw** saws = s->saws;
	int i;
	for (i = 0; i < s->poly; i++) {
		if (check_key(key, saws[i])) {
			saw_off(saws[i]);
		}
	}
}

void synth_free(Synth* s) {
	free(s);
}

float* synth_getBuffer(int bufLenght, void* data) {
	//??
}
