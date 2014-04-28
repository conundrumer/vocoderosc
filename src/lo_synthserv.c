/* Initializes the synthesizer, opens the PortAudio stream, and starts
 * the libLO server. */

#include <stdio.h>
#include <math.h>
#include "portaudio.h"
#include "../headers/synth.h"
#include "../headers/vocoder.h"
#include "../headers/attenuator.h"

#define NUM_VOICES    (12)
#define NUM_BANDS     (100)
#define SAMPLE_RATE   (44100)
#define F_LO          (80)
#define F_HI		  (12000)

// To stop implicit declaration warnings
int openPA(Synth* synth);
void startLO(Synth* synth);

int main();
int main() {
    Synth* synth = synth_new(SAMPLE_RATE, NUM_VOICES);

    if (openPA(synth) == 0) {
        startLO(synth);
    }
    return 0;
}
