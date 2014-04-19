#pragma once

/* Since this audio effect produces control output rather than
 * audio signal output, it needs to call a given function at some
 * interval of volume updates. It gives the callback the volume and
 * whatever callbackparams is.
 */
void* vd_new(void (*callback)(float volume, void* params), void* callbackparams);

/* does not need to return any significant value, but something should get
 * called at the end of the buffer for our project */
float vd_findVolume(float input, int i, int bufLength, void* data);

void vd_free(void* data);
