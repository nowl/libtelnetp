AC_INIT([telnetp], [1.0])
AM_INIT_AUTOMAKE
AM_PROG_LIBTOOL
AC_PROG_CC
AC_CHECK_HEADERS([zlib.h],,[AC_MSG_ERROR([can not find zlib])])
AC_CONFIG_HEADERS([config.h])
AC_CONFIG_SRCDIR([src/test.c])
AC_CONFIG_FILES([Makefile
                  src/Makefile])
AC_OUTPUT
