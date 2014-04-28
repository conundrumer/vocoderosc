/* Initializes the synthesizer, opens the PortAudio stream, and starts
 * the libLO server. */

#include <stdio.h>
#include <string.h>
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
int openPA(Synth* synth, Vocoder* vc, int mode);
// int openPA(Synth* synth);
void startLO(Synth* synth);

int main(int argc, char *argv[]);
int main(int argc, char *argv[]) {
    Synth* synth = synth_new(SAMPLE_RATE, NUM_VOICES);
    Vocoder* vc = vc_new(F_LO, F_HI, NUM_BANDS, SAMPLE_RATE);

    /* Running the synth and vocoder on one computer */
    if (argc == 1) {
    	printf("Running in combined mode\n");
    	if (openPA(synth, vc, 0) == 0) {
    		printf("started stream\n");
    		startLO(synth);
    	}
    }
    /* Runnthing the synth and vocoder separately */
    else if (strcmp(argv[1], "lo") == 0) {
    	printf("Running in lo server mode\n");
    	if (openPA(synth, vc, 1) == 0) {
    		startLO(synth); // Start OSC server
    	}
    } else if (strcmp(argv[1], "vc") == 0) {
    	printf("Running in vocoder mode\n");
    	if (openPA(synth, vc, 2) == 0) {
    		while(1) {} // No OSC server
    	}
    }
    return 0;
}
