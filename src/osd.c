#include "osd.h"
#include "define.h"
#include "../config.h"

xosd* osd_init()
{
    xosd* disp_obj;
    setlocale(LC_ALL, "");
    bindtextdomain (PACKAGE, LOCALEDIR);
    textdomain (PACKAGE);

    
    disp_obj = xosd_create(2);
      if (disp_obj == NULL)
    {
        perror ("Could not create \"osd\"");
    }
        
    xosd_set_timeout(disp_obj, OSD_TIME);
    xosd_set_font (disp_obj, OSD_FONT);
    xosd_set_shadow_offset (disp_obj, 4);
    xosd_set_colour (disp_obj, OSD_COLOR);
    xosd_set_outline_offset(disp_obj, 2);
    xosd_set_outline_colour(disp_obj, OSD_BCOLOR);
    xosd_set_pos (disp_obj, XOSD_bottom);
    xosd_set_vertical_offset (disp_obj, 48);
    xosd_set_align (disp_obj, XOSD_center);
    
    return disp_obj;
}

void osd_bar(xosd* osd, int type, int level) {
    // the size of the increment
    static int inc_size = 100.0 / (MAX_BRIGHT);
    int pos;
        
    char title[127] = {'\0'};
    if (type == OSD_VOLTYPE) {
        sprintf(title, _("Volume"));
        xosd_display (osd, 0, XOSD_string, title);
        xosd_display(osd, 1, XOSD_percentage, level / OSD_VSCALE);
    } else {
        sprintf(title, _("Brightness"));
        xosd_display (osd, 0, XOSD_string, title);
        if (level == MAX_BRIGHT) pos = 100;
        else pos = (level) * inc_size;
        xosd_display (osd, 1, XOSD_slider, pos);
    }
}

void osd_action(xosd* osd, const char* value)
{
	xosd_display(osd, 0, XOSD_string, _("Command"));
	xosd_display (osd, 1, XOSD_string, value);
}
