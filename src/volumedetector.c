#include <stdlib.h>
#include "volumedetector.h"

typedef struct {
	void (*callback)(float volume, void* params);
	void* callbackparams;
	float avg;
} Vd;

void* vd_new(void (*callback)(float volume, void* params), void* callbackparams) {
	Vd* v = malloc(sizeof(Vd));
	v->(*callback) = (*callback);
	v->callbackparams = callbackparams;
	return (void*)v;
}

float vd_findVolume(float input, int i, int bufLength, void* data) {
	Vd* v = (Vd*) data;
	return v->avg;
}

void vd_free(void* data) {
	Vd* v = (Vd*) data;
	free (v);
}
