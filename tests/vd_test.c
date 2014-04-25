#include <stdio.h>
#include <stdlib.h>
#include "../headers/volumedetector.h"

void callback(float volume, void* params) {
	(void) params;
	printf("volume = %f\n", volume);
}


int main() {
	void* params = NULL;
	void* v = vd_new(callback, params);
	int i;
	for (i = 0; i <= 10; i++) {
		float f = 1.0 / (i+1);
		vd_findVolume(f, i, 10, v);		
	}
	return 1;
}
