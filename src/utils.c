#include <math.h>
#include "../headers/utils.h"

float freqtoang (float freq, int fs) {
    return 2*M_PI*freq / (float)fs;
}

float getPeriod(int fs, int key, int f0, int k0, int numkeys) {
    return fs/(f0*powf(2.0,((float)key - k0)/numkeys));
}
