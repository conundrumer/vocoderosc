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
    float nextGain;
    if (at->gain > at->prevGain) {
        nextGain = (1 - at->attack)*at->gain + at->attack*at->prevGain;
    } else {
        nextGain = (1 - at->decay)*at->gain + at->decay*at->prevGain;;
    }
    float slope = (nextGain - at->prevGain)/buflength;
    return slope * input * i;
}

/* changes the gain of the attenuator */
void at_setGain(float prevGain, float newGain, void* data) {
    At* at       = (At*) data;
    at->prevGain = prevGain;
    at->gain     = newGain;
}

void at_free(void* data) {
    At* at = (At*) data;
    free(at);  
}
