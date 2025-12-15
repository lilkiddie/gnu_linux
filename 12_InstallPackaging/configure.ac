AC_INIT([calc], [1.0], [bug-report@example.com])
AM_INIT_AUTOMAKE([-Wall -Wno-error foreign])
AC_PROG_CC
AC_PROG_RANLIB
AM_PROG_AR
LT_INIT

# Simplified gettext
AC_CHECK_HEADERS([libintl.h])
AC_CHECK_FUNCS([setlocale])

AC_CHECK_LIB([m], [pow])

AC_CHECK_PROGS([DOXYGEN], [doxygen])
if test -z "$DOXYGEN"; then
   AC_MSG_WARN([Doxygen not found - continuing without Doxygen support])
fi
AM_CONDITIONAL([HAVE_DOXYGEN], [test -n "$DOXYGEN"])

AC_CONFIG_HEADERS([config.h])
AC_CONFIG_FILES([
 Makefile
 src/Makefile
 tests/Makefile
 po/Makefile
 man/Makefile
 doc/Makefile
])

AC_OUTPUT
