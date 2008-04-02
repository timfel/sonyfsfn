#include "fsfn_brightness.h"

/* Return current brightness of the screen */
int getBrightness() {
    FILE* handle;
    int ret;
   
    if ((handle=fopen("/sys/class/backlight/sony/brightness","rb"))==NULL) {
        perror("Error opening /sys/class/backlight/sony/brightness");
        exit(-1);
    }
    if (fscanf(handle,"%d",&ret)!=1) {
        perror("Error reading /sys/class/backlight/sony/brightness");
        exit(-1);
    }
    fclose(handle);
    return ret;
}

/* Set the current brightness of the screen */
void setBrightness(int b) {
    FILE* handle;

    // validate values
    if (b > MAX_BRIGHT) {
        b = MAX_BRIGHT;
    } else if (b < MIN_BRIGHT) {
        b = MIN_BRIGHT;
    }
   
    if ((handle=fopen("/sys/class/backlight/sony/brightness","wb"))==NULL) {
        perror("Error opening /sys/class/backlight/sony/brightness");
        exit(-1);
    }
    if (fprintf(handle,"%d",b)!=1) {
        perror("Error writing /sys/class/backlight/sony/brightness");
        exit(-1);
    }
    fclose(handle);
}
