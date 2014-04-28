#pragma once

void* vd_new();

/* does not need to return any significant value, but something should get
 * called at the end of the buffer for our project */
float vd_findVolume(float input, int i, int bufLength, void* data);

void vd_free(void* data);

// pointer to volume
float* vd_getVolumePointer(void* data);
