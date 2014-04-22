#pragma once
/**
 * synth: idk up to you to define the interface
 * 
 */

#include "saw.h"


typedef struct {
	int poly; // # of voices
	int numactive;
	Saw** saws;
} Synth;

Synth* synth_new(int fs, int numvoices);

void synth_on(int key, Synth* s);

void synth_off(int key, Synth* s);

/* given synth data, get a buffer of the waveform of length bufLength */
float* synth_getBuffer(int bufLength, void* data);

void synth_free(Synth* s);
