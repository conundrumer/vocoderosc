#include <stdlib.h>
#include <math.h>
#include "../headers/fx_multiband.h"
#include "../headers/bandpass.h"
#include "../headers/fx.h"

#define FUDGE_FACTOR 1.5

/**
 * Mb:
 * Contains an array of bandpass filters and an array of Fx's.
 */
typedef struct {
    int numBands;
    Fx** bands;
    Fx** fxs;
} Mb;

/**
 * getBandEdge: 
 * Gets the frequency at the edge of the band. Used to initialize a new
 * bandpass filter. n goes from 0 to numBands, inclusive, since these are edges
 */
float getBandEdge(float f_low, float f_high, int numBands, int n) {
    return f_low * pow(f_high/f_low, (float)n / (float)numBands);
}

/**
 * mb_new:
 * Mallocs an array of bandpass filters and Fx's and initializes each one.
 */
void* mb_new(float f_low, float f_high, int numBands, int fs) {
    Mb* mb       = malloc(sizeof(Mb));
    // mb->bp       = fx_new(bp_filter, bp_free, bp_new((f_high + f_low)/2, (f_high - f_low), fs));
    mb->bands    = malloc(numBands*sizeof(void*));
    mb->fxs      = malloc(numBands*sizeof(void*));
    mb->numBands = numBands;
    int b;
    for (b = 0; b < numBands; b++) {
        float f_l = getBandEdge(f_low, f_high, numBands, b);
        float f_h = getBandEdge(f_low, f_high, numBands, b+1);
        float fc  = (f_h + f_l) / 2.0; // freq center
        float bw  = (f_h - f_l);       // bandwidth
        mb->bands[b] = fx_new(bp_filter, bp_free, bp_new(fc, bw, fs));
        mb->fxs[b]   = malloc(sizeof(Fx));
    }
    return (void*) mb;
}

/**
 * mb_filter: Applies each bandpass filter and uses the output to apply the Fx.
 */
float mb_filter(float input, int i, int bufLength, void* data) {
    Mb* mb = (Mb*) data;
    float mb_out = 0;
    int b;
    for (b = 0; b < mb->numBands; b++) {
        float bp_out = fx_process(mb->bands[b], input, i, bufLength);
        if (mb->fxs[b] != NULL) {
            mb_out += fx_process(mb->fxs[b], bp_out, i, bufLength);
        } else {
            mb_out += bp_out; // default is wire
        }
    }
    // return fx_process(mb->bp, mb_out, i, bufLength);
    return mb_out / FUDGE_FACTOR;
}

/**
 * mb_free: Frees each bandpass filter and Fx.
 */
void mb_free(void* data) {
    Mb* mb = (Mb*) data;
    int b;
    for (b = 0; b < mb->numBands; b++) {
        fx_free(mb->bands[b]);
        if (mb->fxs[b] != NULL) {
            fx_free(mb->fxs[b]);
        }
    }
    free(mb->bands);
    free(mb->fxs);
}

/**
 * mb_addFx: Adds a new to the the array of Fx's using band as the index.
 */
void mb_addFx(Fx* fx, int band, void* data) {
    Mb* mb = (Mb*) data;
    mb->fxs[band] = fx; 
}