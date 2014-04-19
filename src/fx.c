#include <stdlib.h>
#include "fx.h"

Fx* fx_new(AudioFx audioFx, void* fxData) {
    Fx* fx = malloc(sizeof(Fx));
    fx->audioFx = audioFx;
    fx->fxData = fxData;
    return fx;
}

float fx_process(Fx* fx, float input, int i, int bufLength) {
    return fx->audioFx(input, i, bufLength, fx->fxData);
}

void fx_free(Fx* fx, void (*fxData_free)(void* fxData)) {
    if (fx->fxData != NULL) {
        fxData_free(fx->fxData);
    }
    free(fx);
}
