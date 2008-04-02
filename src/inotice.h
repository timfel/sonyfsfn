#ifndef INOTICE_H
#define INOTICE_H

#include <sys/inotify.h>
#include <stdlib.h>
#include <stdio.h>

/* size of the event structure, not counting name */
#define EVENT_SIZE  (sizeof (struct inotify_event))

/* reasonable guess as to size of 1024 events */
#define BUFF_SIZE        (1024 * (EVENT_SIZE + FILENAME_MAX))

int in_init(char* filename, uint32_t imask);
int in_get (int fd);

#endif
