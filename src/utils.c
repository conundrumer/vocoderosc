#include <math.h>
#include "utils.h"

float freqtoang (float freq, int fs) {
	return 2*M_PI*freq / (float)fs;
}