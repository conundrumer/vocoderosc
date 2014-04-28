#pragma once
#include "saw.h"

/**
 * Synth: Contains the number of and array of saw waves for use
 */
typedef struct {
    int poly; // # of voices
    Saw** saws;
} Synth;

/** 
 * synth_new: allocates and returns a new Synth
 */
Synth* synth_new(int fs, int numvoices);

/** 
 * synth_on:
 * checks for an available saw. if it finds one, plays turns the saw on
 */
void synth_on(int key, Synth* s);

/**
 * synth_off:
 * checks for the saw corresponding to the key. when found, turns it off
 */
void synth_off(int key, Synth* s);

/**
 * synth_allOff(Synth* s): turns off all saws of the synth
 */
 void synth_allOff(Synth* s);

/**
 * synth_getNext:
 * given synth data, get the ith sample of the waveform
 */
float synth_getNext(Synth* s);

/**
 * synth_free: frees the memory allocated for the synth
 */
void synth_free(Synth* s);
