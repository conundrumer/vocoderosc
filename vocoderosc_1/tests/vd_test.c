#include <stdio.h>
#include <stdlib.h>
#include "../headers/volumedetector.h"

int main() {
    void* v = vd_new();
    int i;
    for (i = 0; i <= 10; i++) {
        float f = 1.0 / (i+1);
        vd_findVolume(f, i, 10, v);
    }
    return 1;
}
