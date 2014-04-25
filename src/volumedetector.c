#include <stdlib.h>
#include "../headers/volumedetector.h"

typedef struct {
    VdCallback callback;
    void* callbackparams;
    float avg;
} Vd;

void* vd_new(VdCallback callback, void* callbackparams) {
    Vd* v             = malloc(sizeof(Vd));
    v->avg            = 0;
    v->callback       = callback;
    v->callbackparams = callbackparams;
    return (void*)v;
}

float vd_findVolume(float input, int i, int bufLength, void* data) {
    Vd* v = (Vd*) data;
    if(i == bufLength){
        v->callback(v->avg, v->callbackparams);
        v->avg = 0;
    }
    else if (i < bufLength) {
        // printf("before = %f\n", v->avg);
        // printf("input = %f\n", input);
        v->avg += (input * input) / (float)(bufLength);
        // printf("after = %f\n", v->avg);  
    }
    return v->avg;
}

void vd_free(void* data) {
    Vd* v = (Vd*) data;
    free(v->callbackparams);
    free (v);
}
