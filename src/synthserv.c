#include <stdio.h>
#include <math.h>
#include "portaudio.h"
#include "../headers/synth.h"
#include "../headers/attenuator.h"

#define NUM_VOICES    (12)
#define NUM_SECONDS   (4)
#define SAMPLE_RATE   (44100)

// To stop implicit declaration warnings
int openPA(Synth* synth);
void startLO(Synth* synth);

int main();
int main() {
	Synth* synth = synth_new(SAMPLE_RATE, NUM_VOICES);
	
	if (openPA(synth) == 0) {
		printf("starting LO server\n");
		startLO(synth);
	}
	return 0;
}
