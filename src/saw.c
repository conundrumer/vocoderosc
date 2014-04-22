#include <stdlib.h>
#include <stdio.h>
#include "saw.h"

Saw* saw_new(int fs) {
	Saw* saw = malloc(sizeof(Saw*));
	saw->fs = fs;
	saw->key = -1;
	saw->period = 0; // length of time for 1 cycle
	saw->phase = 0.0f;
	return saw;
}

int check_key(int key, Saw* saw) {
	return (key == saw->key);
}

void saw_on(int key, Saw* saw) {
	saw->key = key;
	saw->period = 13-key;
	printf("period: %d\n", saw->period);
}

void saw_off(Saw* saw) {
	saw->key = -1;
}