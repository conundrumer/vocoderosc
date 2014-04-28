#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include "../headers/synth.h"
#include "../headers/utils.h"

/**
 * Synth: Contains the number of and array of saw waves for use
 */

void printChart(Synth* s);

/** 
 * synth_new: allocates and returns a new Synth
 */
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

/** 
 * synth_on:
 * checks for an available saw. if it finds one, turns the saw on
 */
void synth_on(int key, Synth* s) {
    Saw** saws = s->saws;
    int i;
    for (i = 0; i < s->poly; i++) {
        if (check_key(-1, saws[i])) { // this saw is not active
            saw_on(key, saws[i]);
            // printChart(s);
            return;
        }
    }
    // printf("could not find available saw\n");
    // printChart(s);
    return;
}

/**
 * synth_off:
 * checks for the saw corresponding to the key. when found, turns it off
 */
void synth_off(int key, Synth* s) {
    Saw** saws = s->saws;
    int i;
    for (i = 0; i < s->poly; i++) {
        if (check_key(key, saws[i])) {
            saw_off(saws[i]);
            // printChart(s);
            return;
        }
    }
    // printf("Tried to turn off key %d but could not find it\n", key);
    // printChart(s);
    return;
}

/**
 * synth_allOff(Synth* s): turns off all saws of the synth
 */
void synth_allOff(Synth* s) {
    Saw** saws = s->saws;
    int i;
    for (i = 0; i < s->poly; i++) {
        saw_off(saws[i]);
    }
    // printChart(s);
    return;
}

/**
 * synth_free: frees the memory allocated for the synth
 */
void synth_free(Synth* s) {
    free(s->saws);
    free(s);
}

/**
 * synth_getNext:
 * given synth data, get the ith sample of the waveform
 */
float synth_getNext(Synth* s) {
    int i;
    Saw** saws = s->saws;
    float sample = 0.0;
    for (i = 0; i < s->poly; i++) {
        sample += saw_getNext(saws[i]);
    }
    return sample;
}

/* just a helpful function for printing out keys for all saws */
void printChart(Synth* s) {
    int i;
    printf(".............\n Saw\tKey\t\n.............\n");
    for (i = 0; i < s->poly; i++) {
        printf(" %d\t%d\n",i,s->saws[i]->key);
    }
    printf("\n");
}
