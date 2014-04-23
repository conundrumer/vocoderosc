#include "vocodercarrier.h"
#include "bandVolume.h"
#include "attenuator.h"

typedef struct{
	float f_low;
	float f_high;
	int numBands;
	int fs;
} Vcc;

// frequency range from f_low to f_high
// in numBands bands of constant q
// ie logarithmically spaced
void* vcc_new(float f_low, float f_high, int numBands, int fs) {
	Vcc* vcc = malloc(sizeof(Vcc));
	vcc->f_low = f_low;
	vcc->f_high = f_high;
	vcc->numBands = numBands;
	vcc->fs = fs;
	return (void*)vcc;
}

float vcc_filter(float input, int i, int bufLength, void* data) {
	Vcc* vcc = (Vcc*) data;

}

void vcc_free(void* data) {
	Vcc* vcc = (Vcc*) vcc;
	free(vcc);
}

// VdCallback for vocodermodulator, bandVolume is BandVolume*
void vcc_setBandVolume(float volume, void* bandVolume) {
	BandVolume* bv = (BandVolume*) bandVolume;
	At* at = at_new(); // add attack and delay
	at_setGain(volume, at);
	mb_addFx(vcc_filter, bv->band)
}