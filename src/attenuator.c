#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include "../headers/attenuator.h"

/**
 * The attenuator transitions samples from the synthesizer to
 * volumes determined by volume detectors filtering voice input
 */

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
    at->prevGain = 0.0;
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
    return (slope*i + at->prevGain) * input;
}

/* changes the gain of the attenuator */
void at_setGain(float newGain, void* data) {
    At* at       = (At*) data;
    at->prevGain = at->gain;

    if (newGain > at->gain) {
        at->gain = (1 - at->attack)*newGain + at->attack*at->gain;
    } else {
        at->gain = (1 - at->decay)*newGain + at->decay*at->gain;
    }
}

void at_free(void* data) {
    At* at = (At*) data;
    free(at);  
}
