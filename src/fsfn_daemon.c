#include "define.h"
#include "fsfn_sound.h"
#include "fsfn_brightness.h"

#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/ioctl.h>

// input thing
#include <linux/input.h>

// communications
#include "inotice.h"

// keys
#define  FN_INPUT_VALUE 245     // Fn key generate a 245 value
#define  FN_INPUT_TYPE 4        // a 4 type
#define  FN_INPUT_CODE 4        // and a 4 code

// Pool the fnkey status
int getCodes() {
    FILE* handle;
    int ret;
    if ((handle=fopen("/sys/devices/platform/sony-laptop/fnkey","rb"))==NULL) 
    {
        perror("Error opening /sys/devices/platform/sony-laptop/fnkey");
        exit(-1);
    }
    if (fscanf(handle,"%d",&ret)!=1) {
        perror("Error reading /sys/devices/platform/sony-laptop/fnkey");
        exit(-1);
    }
    fclose(handle);
    return ret;   
}

int fileops(int type, int value) {
    FILE* s;
    s = fopen(OUTFILE, "w");
    if (s != NULL) {
        fprintf(s, "%d %d\n", type, value);
        fclose(s);
        return 0;
    } else
        return -1;
}

// main and loop
int main(int argc, char **argv) {
    // event interface
    int fd = -1;                /* the file descriptor for the device */
    int i;                      /* loop counter */
    size_t read_bytes;          /* how many bytes were read */
    struct input_event ev[64];  /* the events (up to 64 at once) */
      
    /* key code */
    int key;

    /* used if event hit fn */
    int hasSomething;
    
    /* Volume */
    int value = 0;

    /* open event interface*/
    if (argc != 2) {
        /* i don't like outputs...
        fprintf(stderr, "Using /dev/input/event1 for input\n");
        fprintf(stderr, "Overide with %s event-device\n", argv[0]);
        */
        if ((fd = open("/dev/input/event1", O_RDONLY)) < 0) {
            perror("event interface open failed");
            exit(1);
        }
    } else {   
        if ((fd = open(argv[1], O_RDONLY)) < 0) {
            perror("event interface open failed");
            exit(1);
        }
    }

    nice(10); // be a nice dirty code (less dirty but keep nice)

    while(1) {          /* loop */
        hasSomething=0; /* nothing yet */
      
        /* read the event interface */
        read_bytes = read(fd, ev, sizeof(struct input_event) * 64);
      
        if (read_bytes < (int) sizeof(struct input_event)) {
            perror("sonyfn: short read");
            exit (1);
        }

        /* Loop for all readed events until we have something interesting.. */
        for (i = 0;! hasSomething && ( i < (int) (read_bytes /
                                sizeof(struct input_event)) ); i++) {
            hasSomething= (ev[i].type == FN_INPUT_TYPE)
                && (ev[i].code == FN_INPUT_CODE)
                && (ev[i].value == FN_INPUT_VALUE);
          }

        /* If we got a FN event, plz do something...*/
        if ( hasSomething && (key=getCodes()) ) {
            if ((key & FN_F5)==FN_F5) { // lower brightness
                setBrightness(getBrightness()-1);
                fileops(FN_F5, getBrightness());
            }
            if ((key & FN_F6)==FN_F6) { // higher brightness
                setBrightness(getBrightness()+1);
                fileops(FN_F6, getBrightness());
            }
            if ((key & FN_F2)==FN_F2){
                mute();
                fileops(FN_F2, 0);
            }
            if ((key & FN_F3)==FN_F3) {
                volume_down();
                get_volume(&value);
                fileops(FN_F3, value);
            }
            if ((key & FN_F4)==FN_F4) {
                volume_up();
                get_volume(&value);
                fileops(FN_F4, value);
            }
            if ((key & FN_F7)==FN_F7) {
                fileops(FN_F7, 0);
		usleep(100000);
                fileops(0, 0);
            }
            if ((key & FN_F10)==FN_F10) {
                fileops(FN_F10, 0);
		usleep(100000);
                fileops(0, 0);
            }
            if ((key & FN_F12)==FN_F12) {
                fileops(FN_F12, 0);
		usleep(100000);
                fileops(0, 0);
            }     
        }
    }// while
   
    close(fd);
    return 0;
} 

