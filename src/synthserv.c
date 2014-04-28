/* Initializes the synthesizer and opens a PortAudio stream. This version
 * is for a computer only running the vocoder process. */

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
#define F_HI          (12000)

// To stop implicit declaration warnings
int openPA(Vocoder* vc);

int main();
int main() {
    Vocoder* vc = vc_new(F_LO, F_HI, NUM_BANDS, SAMPLE_RATE);

    if (openPA(vc) == 0) {
        while (1) {} // no OSC server
    }
    return 0;
}
