#include <stdlib.h>
#include "attenuator.h"

typedef struct {
  float attack;
  float decay;
} At;

/*
 * attack: how gradually the gain will increase, if the gain changes
 * decay: how gradually gain will decrease
 */
void* at_new(float attack, float decay) {
  At* at = malloc(sizeof(At));
  at->attack = attack;
  at->decay = decay;
  return (void*)at;
}

/*
 * attentuates gradually, from start of the buffer to 
 * end of buffer from previous gain to current gain, with some
 * adjustments from attack/decay
 */
float at_filter(float input, int i, int buflength, void* data) {
  At* at = (At*)data;
  
  for (int j = 0; j < buflength; j++) {
    printf("Looping\n");
  }
  return input;
  
}

void at_free(void* data) {
  At* at = (At*)data;
  free(at);
}

/* changes the gain of the attenuator */
//void at_gain(float gain, void* data);
