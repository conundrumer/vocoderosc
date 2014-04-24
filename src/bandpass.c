#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "bandpass.h"
#include "utils.h"

#define POLES 2

// second order bandpass filter
typedef struct {
	float G;
	float A[POLES];
	float a[POLES];
} Bp;

/**
 * y[n] = G*x[n] + 2*a*cos(wc) * y[n-1] - a^2 * y[n-2],
 * G    = (1-a) * sqrt(a^2 - 2*cos(2*wc)*a + 1),
 * a    = 2 - cos(bw/2) - sqrt(3 - 4*cos(bw/2) + cos^2(bw/2)),
 * wc   = 2*pi*fc / fs
*/
void* bp_new(float freq, float bw, int fs) {
	float wc = freqtoang(freq, fs);
	float wb = freqtoang(bw, fs)/2.0; // angular bandwidth
	Bp* bp   = malloc(sizeof(Bp));
	// printf("wc: %f, wb: %f\n", wc, wb);

	float a  = 2.0 - cos(wb) - sqrt(3.0 - 4.0*cos(wb) + cos(wb)*cos(wb));
	bp->G    = (1.0-a) * sqrt(a*a - 2.0*cos(2.0*wc)*a + 1.0);
	bp->A[0] = 2.0*a*cos(wc);
	bp->A[1] = -1.0 * a*a;

	// printf("G: %f, A1: %f, A2: %f\n", bp->G, bp->A[0], bp->A[1]);
	return bp;
}

float bp_filter(float input, int i, int bufLength, void* data) {
	(void) i;
	(void) bufLength;
	Bp* bp = (Bp*) data;
	float output = bp->G * input + bp->A[0] * bp->a[0] + bp->A[1] * bp->a[1];
	bp->a[1] = bp->a[0];
	bp->a[0] = output;
	return output;
}

void bp_free(void* data) {
	Bp* bp = (Bp*) data;
	free(bp);
}
