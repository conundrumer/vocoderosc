#pragma once

/**
 * Saw:
 * Represents one saw wave with fields fs (frequency sampling rate), key
 * (from {-1U[1,12]}, where -1 means the inactive), and period.
*/
typedef struct {
	int fs;
	int key; // -1 means off
	int period;
	float currentSample;
} Saw;

/**
 * saw_new: allocates and returns a new saw
 */
Saw* saw_new(int fs);

/**
 * check_key: returns if the input key matches the key of the input saw
 */
int check_key(int key, Saw* saw);

/**
 * saw_on: sets the key and period of saw to match the input
 */
void saw_on(int key, Saw* saw);

/**
 * saw_off: sets the key to -1 and period to 0
 */
void saw_off(Saw* saw);

/**
 * saw_free: frees memory allocated for the saw
 */
 void saw_free(Saw* saw);

/**
 * saw_getNext: calculates and returns the next sample. updates
 *              currentSample
 */
float saw_getNext(Saw* saw);
