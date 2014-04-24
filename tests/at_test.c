#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include "../src/attenuator.h"

int main() {
    int i;
    float x;
    int buflength   = 25;
    float prev      = 0.0;
    float* sintable = malloc(buflength*sizeof(float));
    float* ones     = malloc(buflength*sizeof(float));

    for (i = 0; i < buflength; i++) {
        x    = (3*M_PI*i) / buflength;
        prev = sin(x);
        sintable[i] = prev;
    }

    for (i = 0; i < buflength; i++) {
        ones[i] =1.0;
    }

    void* at = at_new(1.0, 1.0);
    at_setGain(8.0, at);
    float filtered;
    printf("\nOnes\ngain = 8.0\n......................................\n\
i\torig\t\tnew\n......................................\n");
    
    for (i = 0; i < buflength; i++) {
        filtered = at_filter(ones[i], i, buflength, at);
        printf("%d\t%f\t%f\n",i,ones[i],filtered);
    }
    printf("\nSin\ngain = 8.0\n......................................\n\
i\torig\t\tnew\n......................................\n");
    for (i = 0; i < buflength; i ++) {
        filtered = at_filter(sintable[i],i,buflength,at);
        printf("%d\t%f\t%f\n",i,sintable[i],filtered);
    }

    return 0;
}