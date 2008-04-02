#ifndef ONSCR_H
#define ONSCR_H

// osd stuff
#include <xosd.h>
#include <locale.h>
#include <X11/Xlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/ioctl.h>
#include <stdio.h>

// gettext stuff
#include <libintl.h>
#define _(String) gettext (String) 

// the osd color
#define OSD_COLOR "green1"
// the shadow osd color
#define OSD_BCOLOR "black"
// the osd font... change the 7th position for size
// or use xfontsel to explore the options
#define OSD_FONT "-b&h-*-bold-r-*-*-34-*-*-*-*-*-*-*"
// the length of time the osd is shown
#define OSD_TIME 3

// volume scaling factor for OSD
#define OSD_VSCALE 250

#define OSD_VOLTYPE 0
#define OSD_BRITYPE 1

#define MAX_BRIGHT 7

xosd* osd_init();
void osd_bar(xosd* osd, int type, int level);
void osd_action(xosd* osd, const char* value);

#endif
