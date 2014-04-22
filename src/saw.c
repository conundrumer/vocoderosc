#include <stdlib.h>
#include "saw.h"

Saw* saw_new(int fs) {
	Saw* saw = malloc(sizeof(Saw*));
	saw->fs = fs;
	saw->key = -1;
	saw->period = 0;
	saw->phase = 0;
	return saw;
}

int check_key(int key, Saw* saw) {
	return (key == saw->key);
}

void saw_on(int key, Saw* saw) {
	saw->key = key;
}

void saw_off(Saw* saw) {
	saw->key = -1;
}