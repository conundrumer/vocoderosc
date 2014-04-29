/**
 * Saw:
 * Represents one saw wave with fields fs (frequency sampling rate), key
 * (from {-1U[1,12]}, where -1 means the inactive), and period.
*/

#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include "../headers/saw.h"
#include "../headers/utils.h"

#define F0 (65.4064)
#define K0 (1)
#define NUM_KEYS (12)

/**
 * saw_new: allocates and returns a new saw
 */
Saw* saw_new(int fs) {
    Saw* saw = malloc(sizeof(Saw));
    saw->fs  = fs;
    saw->key = -1;
    saw->currentSample = 0.0;
    return saw;
}

/**
 * check_key: returns if the input key matches the key of the input saw
 */
int check_key(int key, Saw* saw) {
    return (key == saw->key);
}

/**
 * saw_on: sets the key and period of saw to match the input
 */
void saw_on(int key, Saw* saw) {
    saw->key = key;
}

/**
 * saw_off: sets the key to -1 and period to 0
 */
void saw_off(Saw* saw) {
    saw->key = -1;
    saw->currentSample = 0.0;
}

/**
 * saw_getNext: calculates and returns the sample. updates
 *              currentSample
 */
float saw_getNext(Saw* saw) {
    if (saw->key > -1) {
        // float period = (saw->fs)/(F0*powf(2.0,((float)(saw->key)-K0)/NUM_KEYS));
        float period = getPeriod(saw->fs, saw->key, F0, K0, NUM_KEYS);
        float slope  = 2.0/period;
        saw->currentSample += slope;
        // Drop when sample exceeds 1.0
        if (saw->currentSample > 1.0f) {
            saw->currentSample -= 2.0f;
        }
        return saw->currentSample;
    }
    return saw->currentSample;
}

/**
 * saw_free: frees memory allocated for the saw
 */
void saw_free(Saw* saw) {
    if (saw != NULL) {
        free(saw);
    }
}
