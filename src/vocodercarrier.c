#include <stdlib.h>
#include "../headers/vocodercarrier.h"
#include "../headers/bandvolume.h"
#include "../headers/attenuator.h"
#include "../headers/fx_multiband.h"

typedef struct {
    int    numBands;
    void** ats;
    Fx*    mb;
} Vcc;

// Frequency ranges from f_low to f_high in numBands bands of constant q
// (i.e. logarithmically spaced)
void* vcc_new(float f_low, float f_high, int numBands, int fs) {
    int i;
    Vcc* vcc    = malloc(sizeof(Vcc));
    void** ats  = malloc(numBands*sizeof(void*));
    void* rawMb = mb_new(f_low, f_high, numBands, fs);
    Fx* mb      = fx_new(mb_filter, mb_free, rawMb);
    for (i = 0; i < numBands; i++) {
        void* rawAt = at_new(1.0, 1.0); 
        ats[i]      = rawAt;
        mb_addFx(fx_new(at_filter, at_free, rawAt), i, rawMb);
    }
    vcc->numBands = numBands;
    vcc->ats      = ats;
    vcc->mb       = mb;
    return (void*) vcc;
}

float vcc_filter(float input, int i, int bufLength, void* data) {
    Vcc* vcc = (Vcc*) data;
    return fx_process(vcc->mb, input, i, bufLength);
}

void vcc_free(void* data) {
    Vcc* vcc = (Vcc*) data;
    fx_free(vcc->mb);
    free(vcc->ats);
    free(vcc);
}

// VdCallback for vocodermodulator. bandVolume has type BandVolume*
// Sets the gain for a band's attenuator to the input volume
void vcc_setBandVolume(float volume, void* bandVolume) {
    BandVolume* bv = (BandVolume*) bandVolume;
    Vcc* vcc       = (Vcc*) (bv->data);
    void* at       = vcc->ats[bv->band];
    at_setGain(volume, at);
}
