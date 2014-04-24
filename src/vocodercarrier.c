#include <stdlib.h>
#include "vocodercarrier.h"
#include "bandVolume.h"
#include "attenuator.h"
#include "fx_multiband.h"

typedef struct {
	int numBands;
	Fx* mb;
	void** ats;
} Vcc;

// frequency range from f_low to f_high
// in numBands bands of constant q
// ie logarithmically spaced
void* vcc_new(float f_low, float f_high, int numBands, int fs) {
	Vcc* vcc = malloc(sizeof(Vcc));
	void* rawMb = mb_new(f_low, f_high, numBands, fs);
	Fx* mb = fx_new(mb_filter, mb_free, rawMb);
	int i;
	void** ats = malloc(numBands*sizeof(void*));
	for (i = 0; i < numBands; i++) {
		void* rawAt = at_new(1.0, 1.0);	
		Fx* at = fx_new(at_filter, at_free, rawAt);
		mb_addFx(at, i, rawMb);
		ats[i] = rawAt;
	}
	vcc->mb = mb;
	vcc->numBands = numBands;
	vcc->ats = ats;
	return (void*)vcc;
}

float vcc_filter(float input, int i, int bufLength, void* data) {
	Vcc* vcc = (Vcc*) data;
	float output = fx_process(vcc->mb, input, i, bufLength);
	return output;
}

void vcc_free(void* data) {
	Vcc* vcc = (Vcc*) data;
	free(vcc->ats);
	fx_free(vcc->mb);
	free(vcc);
}

// VdCallback for vocodermodulator, bandVolume is BandVolume*
void vcc_setBandVolume(float volume, void* bandVolume) {
	BandVolume* bv = (BandVolume*) bandVolume;
	Vcc* vcc = (Vcc*)(bv->data);
	void* at = vcc->ats[bv->band];
	at_setGain(volume, at);
}

int main() {
	int fs = 20;
	float f_low = 2.0;
	float f_high = 8.0;
	int numBands = 10;
	void* vcc = vcc_new(f_low, f_high, numBands, fs);
	Fx* fx = fx_new(vcc_filter, vcc_free, vcc);
	float impulse = 1.0;
    int i;
    printf("Testing impulse response...\n");
    int bufLength = 32;
    BandVolume* bv = malloc(sizeof(BandVolume));
    bv->band = 5;
    bv->data = vcc;
   	// vcc_setBandVolume(0.1, bv);
    for (i = 0; i < bufLength+1; i++) {
        float output = fx_process(fx, impulse, i, bufLength);
        impulse = 0;
		printf("%i: %f\n", i, output);
    }
	fx_free(fx);
	return 0;
}

// int main() {
// 	void* vcc = vcc_new(1.0, 1.0, 5, 44100);
// 	float output = vcc_filter(0.1, 2, 64, vcc);
// 	BandVolume* bv = malloc(sizeof(BandVolume));
// 	bv->band = 2;
// 	bv->data = vcc;
// 	vcc_setBandVolume(5, bv);
// 	vcc_free(vcc);
// 	free(bv);
// 	return 0;
// }