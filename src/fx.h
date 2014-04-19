#pragma once

/**
 * AudioFX:
 * Takes a sample input, the position in the buffer, the length of the buffer,
 * and audio effect data (eg parameters), and returns the output of the effect.
 */
typedef float (*AudioFx)(float input, int i, int bufLength, void* fxData);

/**
 * Fx:
 * An audio effect psuedo-class, containing the function that processses the
 * effect and saved data for the effect.
 */
typedef struct {
    AudioFx audioFx;
    void* fxData;
} Fx;

/**
 * fx_new: allocates and returns a new Fx,
 * assuming fxData has already been allocated/initialized
 */
Fx* fx_new(AudioFx audioFx, void* fxData);

/**
 * fx_process: returns the output of audio effects processing
 */
float fx_process(Fx* fx, float input, int i, int bufLength);

/**
 * fx_free: frees fx and uses fxData_free to free fxData
 */
void fx_free(Fx* fx, void (*fxData_free)(void* fxData));
