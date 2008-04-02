#ifndef FSFN_SOUND_H
#define FSFN_SOUND_H

// sound stuff
#include <fcntl.h>
#include <linux/soundcard.h>
#include <sys/ioctl.h>

// config hard coded :p
#define  MIXER_DEV   "/dev/mixer"

int oldvalue;

int get_volume(int *value);
int set_volume(int *value);
int volume_up();
int volume_down();
int mute();



#endif
