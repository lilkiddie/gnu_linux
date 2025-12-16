AC_PREREQ([2.71])
AC_INIT([buf], [1.00], [google@gmail.com])
AM_INIT_AUTOMAKE([foreign])
LT_INIT([disable-static])
AC_CONFIG_SRCDIR([src/buf.c])
AC_CONFIG_HEADERS([config.h])

AC_PROG_CC

PKG_CHECK_MODULES([CHECK],[check])

# Variable definitins
AC_SUBST(CK_VERBOSITY, verbose)
AC_ARG_VAR(CK_VERBOSITY, [Default: "verbose", can be "silent", "minimal" or "normal")])
# Enabe/disable things
AC_ARG_ENABLE([gcov],
              [AS_HELP_STRING([--enable-gcov], [use Gcov to test the test suite])],
              [], [enable_gcov=no])
AM_CONDITIONAL([COND_GCOV],[test '!' "$enable_gcov" = no])

AC_CHECK_HEADERS([stddef.h stdlib.h])

AC_CHECK_TYPES([ptrdiff_t])

AC_FUNC_MALLOC
AC_CHECK_FUNCS([memset strchr])

AC_CONFIG_FILES([Makefile
                 tests/Makefile
                 src/Makefile])
AC_OUTPUT
