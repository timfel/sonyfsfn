#include "inotice.h"
#include "osd.h"
#include "define.h"
#include "../config.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <pthread.h>

#define CR 13            /* Decimal code of Carriage Return char */
#define LF 10            /* Decimal code of Line Feed char */
#define EOF_MARKER 26    /* Decimal code of DOS end-of-file marker */

int fileread(int *value) {
    int type = 0;
    FILE* s;
    char c = '0';
    char buffer[8] = {'\0'};
    
    s = fopen(OUTFILE, "r");
    if (s != NULL) {
        c = fgetc(s);
        while (!(c == CR || c == LF || c == EOF || c == ' ')) {
            strncat(buffer, &c, 1);
            c = fgetc(s);
        }
        type = atoi(buffer);
        
        buffer[0] = '\0';
        c = fgetc(s);
        while (!(c == CR || c == LF || c == EOF || c == ' ')) {
            strncat(buffer, &c, 1);
            c = fgetc(s);
        }
        *value = atoi(buffer);
        
        fclose(s);
        return type;
    } else
        return -1;
}

void actions(xosd* osd, int type, int value) {
    FILE* conf;
    pthread_t cmd;
    char buffer[128] = {'\0'};
    
    if (type == FN_F2 || type == FN_F3 || type == FN_F4)
        osd_bar(osd, OSD_VOLTYPE, value);
    else if (type == FN_F5 || type == FN_F6)
        osd_bar(osd, OSD_BRITYPE, value);
    else if (type == FN_F7) {
        sprintf(buffer, "%s/.fsfnc", getenv("HOME"));
        conf = fopen(buffer, "r");
        if (conf != NULL) {
            fscanf(conf, "%s", buffer);
            fclose(conf);
            pthread_create(&cmd, NULL, system, buffer);
            pthread_detach(cmd);
        }
        osd_action(osd, buffer);
    } else if (type == FN_F10) {
        sprintf(buffer, "%s/.fsfnc", getenv("HOME"));
        conf = fopen(buffer, "r");
        if (conf != NULL) {
            fscanf(conf, "%s", buffer);
            fscanf(conf, "%s", buffer);
            fclose(conf);
            pthread_create(&cmd, NULL, system, buffer);
            pthread_detach(cmd);
        }
        osd_action(osd, buffer);
    } else if (type == FN_F12) {
        sprintf(buffer, "%s/.fsfnc", getenv("HOME"));
        conf = fopen(buffer, "r");
        if (conf != NULL) {
            fscanf(conf, "%s", buffer);
            fscanf(conf, "%s", buffer);
            fscanf(conf, "%s", buffer);
            fclose(conf);
            pthread_create(&cmd, NULL, system, buffer);
            pthread_detach(cmd);
        }
        osd_action(osd, buffer);
    }
}

int main () {
    int ifd;
    int num = 0;
    int val = 0;
    int action = 0;
    xosd* osd;
    
    ifd = in_init(OUTFILE, IN_CLOSE_WRITE);
    osd = osd_init();

    while(1) {
        num = in_get(ifd);
        #ifdef DEBUG
            printf("%d Events recorded\n", num);
            fflush(stdout);
        #endif
        action = fileread(&val);
        #ifdef DEBUG
            printf("Got type %d, and value %d\n", action, val);
            fflush(stdout);
        #endif
        actions(osd, action, val);
    }

    return 0;
}
