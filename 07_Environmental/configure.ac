AC_PREREQ([2.69])
AC_INIT([hasher], [0.1], [support@example.org])
AM_INIT_AUTOMAKE([foreign -Wall -Werror])

AC_CONFIG_SRCDIR([hasher.c])
AC_CONFIG_HEADERS([config.h])

# Check for programs
AC_PROG_CC
AC_PROG_INSTALL

# Check for required library: librhash
PKG_CHECK_MODULES([RHASH], [librhash],
    [],
    [AC_MSG_ERROR([librhash is required but not found])])

# Optional readline support
AC_ARG_ENABLE([readline],
    AS_HELP_STRING([--disable-readline], [disable readline support even if available]),
    [],
    [enable_readline=check])

AS_IF([test "x$enable_readline" != "xno"], [
    PKG_CHECK_MODULES([READLINE], [readline],
        [
            AC_DEFINE([HAVE_LIBREADLINE], [1], [Define if readline is available])
            have_readline=yes
        ],
        [
            AC_CHECK_LIB([readline], [readline],
                [
                    AC_DEFINE([HAVE_LIBREADLINE], [1], [Define if readline is available])
                    READLINE_LIBS="-lreadline"
                    have_readline=yes
                ],
                [
                    if test "x$enable_readline" = "xyes"; then
                        AC_MSG_ERROR([readline support requested but not found])
                    fi
                    have_readline=no
                ])
        ])
], [have_readline=no])

AM_CONDITIONAL([USE_READLINE], [test "x$have_readline" = "xyes"])

# Check for header files
AC_CHECK_HEADERS([stdio.h stdlib.h string.h ctype.h])

# Check for functions
AC_CHECK_FUNCS([strcasecmp strncmp])

AC_CONFIG_FILES([Makefile])
AC_OUTPUT
