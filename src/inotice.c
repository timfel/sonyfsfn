#include "inotice.h"

int in_init(char* filename, uint32_t imask) {
    int ifd;
    int watchdesc;

    ifd = inotify_init();
    if (ifd < 0) {
        return -1;
    }
    
    watchdesc = inotify_add_watch(ifd, filename, IN_CLOSE_WRITE);
    if (watchdesc < 0) {
        return -1;
    }

    return ifd;
}

int in_get(int fd) {
    ssize_t len;
    char buff[BUFF_SIZE] = {0};

    len = read (fd, buff, BUFF_SIZE);

    return len / EVENT_SIZE;
}
