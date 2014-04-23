#include "vocodercarrier.h"
#include "bandVolume.h"
#include "attenuator.h"
#include "fx_multiband.h"

typedef struct {
	float f_low;
	float f_high;
	int numBands;
	int fs;
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
		Fx* at = fx_new(at_filter, at_free, rawAt)
		mb_addFx(at, i, rawMb);
		ats[i] = (void*)rawAt;
	}
	vcc->mb = mb;
	vcc->f_low = f_low;
	vcc->f_high = f_high;
	vcc->numBands = numBands;
	vcc->fs = fs;
	vcc->ats = ats;
	return (void*)vcc;
}

float vcc_filter(float input, int i, int bufLength, void* data) {
	Vcc* vcc = (Vcc*) data;
	fx_process(vcc->mb, input, i, buflength);
}

void vcc_free(void* data) {
	Vcc* vcc = (Vcc*) data;
	mb_free((void*)vcc->mb);
	free(vcc);
}

// VdCallback for vocodermodulator, bandVolume is BandVolume*
void vcc_setBandVolume(float volume, void* bandVolume) {
	BandVolume* bv = (BandVolume*)bandVolume;
	Vcc* vcc = (Vcc*)bv->data;
	void* at = vcc->ats[bv->band];
	at_setGain(volume, at);
	mb_addFx(at, bv->band, vcc->mb);
}