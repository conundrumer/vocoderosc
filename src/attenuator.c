#include <stdlib.h>
#include "attenuator.h"

/*
 * attack: how gradually the gain will increase, if the gain changes
 * decay: how gradually gain will decrease
 */
void* at_new(float attack, float decay);

/*
 * attentuates gradually, from start of the buffer to 
 * end of buffer from previous gain to current gain, with some
 * adjustments from attack/decay
 */
float at_filter(float input, int i, int buflength, void* data) {
  // LOL WUT
  return 1.0;
  
}

void at_free(void* data);

/* changes the gain of the attenuator */
void at_gain(float gain, void* data);
