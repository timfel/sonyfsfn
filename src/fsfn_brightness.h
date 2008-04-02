#ifndef FSFN_BRIGHTNESS_H
#define FSFN_BRIGHTNESS_H

#include <stdio.h>
#include <stdlib.h>

// The FS series seems to support 8 brightness levels
#define MAX_BRIGHT 7
#define MIN_BRIGHT 0

int getBrightness();
void setBrightness(int b);


#endif
