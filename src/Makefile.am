INCLUDES =
AM_LDFLAGS =
AM_CPPFLAGS = -DLOCALEDIR=\"$(localedir)\" -D_REENTRANT
LDADD = @LIBINTL@
localedir = $(datadir)/locale

bin_PROGRAMS = fsfnd fsfnc
fsfnd_SOURCES = fsfn_daemon.c \
		define.h \
		fsfn_brightness.c fsfn_brightness.h \
		fsfn_sound.c fsfn_sound.h 
fsfnc_SOURCES = client.c \
		define.h \
		inotice.c inotice.h \
		osd.c osd.h
fsfnc_LDADD = -lxosd -lpthread
