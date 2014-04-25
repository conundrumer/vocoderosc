#include <stdio.h>
#include <stdlib.h>
#include "../headers/volumedetector.h"

typedef struct {
    float avg;
    float* vol;
} Vd;

void* vd_new() {
    Vd* v     = malloc(sizeof(Vd));
    v->vol    = malloc(sizeof(float));
    v->avg    = 0.0;
    *(v->vol) = 0.0;
    return (void*)v;
}

float vd_findVolume(float input, int i, int bufLength, void* data) {
    Vd* v = (Vd*) data;
    if(i == bufLength){
        *(v->vol) = v->avg;
        v->avg = 0.0;
    }
    else if (i < bufLength) {
        // printf("before = %f\n", v->avg);
        // printf("input  = %f\n", input);
        v->avg += (input * input) / (float)(bufLength);
        // printf("after  = %f\n\n", v->avg);  
    }
    return v->avg;
}

void vd_free(void* data) {
    Vd* v = (Vd*) data;
    free(v->vol);
    free (v);
}

float* vd_getVolumePointer(void* data) {
    Vd* v = (Vd*) data;
    return v->vol;
}
