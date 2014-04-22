#pragma once

typedef struct {
	int fs;
	int key; // -1 means off
	int period;
	int phase;
} Saw;

Saw* saw_new(int fs);

int check_key(int key, Saw* saw);

void saw_on(int key, Saw* saw);

void saw_off(Saw* saw);