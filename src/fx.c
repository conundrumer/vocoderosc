#include <stdio.h>
#include <stdlib.h>
#include "../headers/fx.h"

/**
 * Fx:
 * An audio effect psuedo-class, containing the function that processses the
 * effect and saved data for the effect.
 */
 
/**
 * fx_new: allocates and returns a new Fx,
 * assuming fxData has already been allocated/initialized
 */
Fx* fx_new(AudioFx audioFx, FreeFx freeFx, void* fxData) {
    Fx* fx      = malloc(sizeof(Fx));
    fx->audioFx = audioFx;
    fx->freeFx  = freeFx;
    fx->fxData  = fxData;
    return fx;
}

/**
 * fx_process: returns the output of audio effects processing
 */
float fx_process(Fx* fx, float input, int i, int bufLength) {
    return fx->audioFx(input, i, bufLength, fx->fxData);
}

/**
 * fx_free: frees fx
 */
void fx_free(Fx* fx) {
    if (fx->fxData != NULL) {
        fx->freeFx(fx->fxData);
    }
    free(fx);
}

// returns fx->fxData
void* fx_getData(Fx* fx) {
    return fx->fxData;
}
