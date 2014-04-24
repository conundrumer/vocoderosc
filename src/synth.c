#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include "../headers/synth.h"
#include "../headers/utils.h"

void printChart(Synth* s);

Synth* synth_new(int fs, int numvoices) {
	Synth* synth = malloc(sizeof(Synth));
	synth->saws  = malloc(numvoices*sizeof(Saw*));
	synth->poly  = numvoices;
	int i;
	for (i = 0; i < numvoices; i++) {
		Saw* s_i       = saw_new(fs);
		synth->saws[i] = s_i;
	}
	return synth;
}

void synth_on(int key, Synth* s) {
	Saw** saws = s->saws;
	int i;
	for (i = 0; i < s->poly; i++) {
		if (check_key(-1, saws[i])) { // this saw is not active
			saw_on(key, saws[i]);
			printChart(s);
			return;
		}
	}
	printf("could not find available saw\n");
	printChart(s);
	return;
}

void synth_off(int key, Synth* s) {
	Saw** saws = s->saws;
	int i;
	for (i = 0; i < s->poly; i++) {
		if (check_key(key, saws[i])) {
			saw_off(saws[i]);
			printChart(s);
			return;
		}
	}
	printf("Tried to turn off key %d but could not find it\n", key);
	printChart(s);
	return;
}

void synth_allOff(Synth* s) {
	Saw** saws = s->saws;
	int i;
	for (i = 0; i < s->poly; i++) {
		saw_off(saws[i]);
	}
	printChart(s);
	return;
}

void synth_free(Synth* s) {
	free(s->saws);
	free(s);
}

float* synth_getBuffer(int bufLength, Synth* s) {
	int i, j;
	Saw** saws = s->saws;
	float* outputBuffer = malloc(bufLength*sizeof(float));
	for (i = 0; i < bufLength; i++) {
		float sample = 0.0;
		for (j = 0; j < s->poly; j++) {
			sample += saw_getNext(saws[j]);
		}
		outputBuffer[i] = sample;
	}
	free(outputBuffer);
	return outputBuffer;
}

void printChart(Synth* s) {
	int i;
	printf(".............\n Saw\tKey\t\n.............\n");
	for (i = 0; i < s->poly; i++) {
		printf(" %d\t%d\n",i,s->saws[i]->key);
	}
	printf("\n");
}
