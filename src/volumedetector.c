#include <stdlib.h>
#include "volumedetector.h"

typedef struct {
	void (*callback)(float volume, void* params);
	void* callbackparams;
	float avg;
} Vd;

void* vd_new(void (*callback)(float, void*), void* callbackparams) {
	Vd* v = malloc(sizeof(Vd));
	v->avg = 0;
	v->callback = callback;
	v->callbackparams = callbackparams;
	return (void*)v;
}
// for (int i = 0; i < bufLength; i++) {
//     float input = buffer[i];
float vd_findVolume(float input, int i, int bufLength, void* data) {
	Vd* v = (Vd*) data;
	v->avg += (input * input) / (float)(bufLength);
	if(i == bufLength){
		v->callback(v->avg, v->callbackparams);
		v->avg = 0;
	}
	return v->avg;
}
// }

void vd_free(void* data) {
	Vd* v = (Vd*) data;
	free(v->callbackparams);
	free (v);
}

void callback(float volume, void* params) {
	printf("%f", volume);
}

/*
int main() {
	Vd* v = (Vd*) vd_new(callback, []);
	vd_findVolume(0.5, 0, 1, v);
	return 1;
}
*?
