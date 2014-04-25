#include <stdlib.h>
#include "../headers/fx.h"

Fx* fx_new(AudioFx audioFx, FreeFx freeFx, void* fxData) {
    Fx* fx      = malloc(sizeof(Fx));
    fx->audioFx = audioFx;
    fx->freeFx  = freeFx;
    fx->fxData  = fxData;
    return fx;
}

float fx_process(Fx* fx, float input, int i, int bufLength) {
    return fx->audioFx(input, i, bufLength, fx->fxData);
}

void fx_free(Fx* fx) {
    if (fx->fxData != NULL) {
        fx->freeFx(fx->fxData);
    }
    free(fx);
}

void* fx_getData(Fx* fx) {
    return fx->fxData;
}
