AC_PREREQ([2.69])
AC_INIT([number-game], [1.0], [your@email.org])
AC_CONFIG_SRCDIR([src/guess.c])
AC_CONFIG_HEADERS([config.h])
AM_INIT_AUTOMAKE([foreign subdir-objects])
AC_PROG_CC

AC_CHECK_HEADERS([libintl.h locale.h stdlib.h string.h stdio.h])

AC_CHECK_FUNCS([setlocale])

AC_CONFIG_FILES([Makefile src/Makefile po/Makefile man/Makefile])

AC_OUTPUT
