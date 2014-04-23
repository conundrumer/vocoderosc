#pragma once

// frequency to angular frequency
float freqtoang (float freq, int fs);

// saw data to period
float getPeriod(int fs, int key, int f0, int k0, int numkeys);
