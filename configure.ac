AC_INIT([sonyfsfn],
        [0.0.1],
        [Tim Felgentreff timfelgentreff@gmail.com],
        [sonyfsfn])
AC_CONFIG_AUX_DIR(config)
AM_CONFIG_HEADER(config.h)
AM_INIT_AUTOMAKE([dist-bzip2])

AC_PROG_CC
AC_PROG_INSTALL
AC_AIX
AC_ISC_POSIX
AC_MINIX
AC_STDC_HEADERS
AC_CHECK_HEADERS([pthread.h stdlib.h string.h unistd.h X11/Xdefs.h])
AC_PROG_RANLIB
AM_GNU_GETTEXT([external])

if test "x${prefix}" = "xNONE"; then
   PACKAGE_BIN_DIR="${ac_default_prefix}/bin"
else
   PACKAGE_BIN_DIR="${prefix}/bin"
fi

AC_SUBST(PACKAGE_BIN_DIR)


############# GENTOO ##############
AC_ARG_ENABLE(gentoo,
                 [  --enable-gentoo	enable initscript for gentoo],
                         gentoo="yes", gentoo="no")

if test $gentoo = "yes" ; then
	DISTRO="gentoo"
        cat data/fsfn.gentoo | sed "s#@PREFIX@#$PACKAGE_BIN_DIR#g" > data/fsfn
else
	DISTRO="debian or else"
	cat data/fsfn.debian | sed "s#@PREFIX@#$PACKAGE_BIN_DIR#g" > data/fsfn
fi

chmod +x data/fsfn

############### DEBUG ##############
AC_ARG_ENABLE(debug-mode,
	         [  --enable-debug-mode	enable debug mode],
			 debug="yes", debug="no")
			 
if test $debug = "yes" ; then
	AC_DEFINE(DEBUG, 1, [ ])
fi

############### XOSD ##############
xosd="yes"
AC_CHECK_HEADER(xosd.h,
		[AC_DEFINE(XOSD, 1, [ ])], xosd="no")

if test $xosd = "no" ; then
	echo "ERROR: We require XOSD (libxosd-dev on Debian)"
	exit -1
fi

AC_CONFIG_FILES([ po/Makefile.in
   Makefile
   README
   doc/Makefile
   m4/Makefile
   src/Makefile
   data/Makefile
])

AC_OUTPUT


echo
echo "*********** SONY FS-FN DRIVER *************"
echo "bindir ................................ $PACKAGE_BIN_DIR"
echo "distro ................................ $DISTRO"
echo
echo "make, make install"
