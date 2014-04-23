#include <stdio.h>
#include <math.h>
#include "portaudio.h"
#include "synth.h"
#define NUM_VOICES    (12)
#define NUM_VOICES_KEYBOARD (49)
#define NUM_SECONDS   (4)
#define SAMPLE_RATE   (44100)

int main();
int main() {
	Synth* synth = synth_new(SAMPLE_RATE, NUM_VOICES);
	runPA(synth);
	runServer(synth);
	return 0;
}