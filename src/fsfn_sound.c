#include "fsfn_sound.h"

// SOUND HANDLER

int get_volume(int *value)
{
    int mixer = open(MIXER_DEV, O_RDONLY);

    if (mixer) {
        ioctl(mixer, SOUND_MIXER_READ_VOLUME, value);
        close(mixer);
        return 0;
    }
    else
        return 1;
}

int set_volume(int *value)
{
    int mixer = open(MIXER_DEV, O_RDWR);

    if (mixer) {
        ioctl(mixer, SOUND_MIXER_WRITE_VOLUME, value);
        close(mixer);
        return 0;
    }
    else
        return 1;
}

int volume_up()
{
    int value = 0;

    get_volume(&value);

    if (value < 0x5a5a)
        value += 0x0a0a;
    else
        value = 0x6464;

    set_volume(&value);

    return 0;
}

int volume_down()
{
    int value = 0;

    get_volume(&value);

    if (value > 0x0a0a)
        value -= 0x0a0a;
    else
        value = 0;

    set_volume(&value);

    return 0;
}

int mute()
{
    int value;
   
    get_volume(&value);
   
    if (value) {
       oldvalue=value;
       value=0;
       set_volume(&value);
    }
    else {
       if (!oldvalue) {
      volume_up();       
       }
       else {
          set_volume(&oldvalue);
       }
    }

    return 0;
}
// END OF SOUND
