lib_LTLIBRARIES = libcalc.la
bin_PROGRAMS = calc

libcalc_la_SOURCES = libcalc.c libcalc.h
libcalc_la_CFLAGS = -Wall -Wextra
libcalc_la_LDFLAGS = -version-info 1:0:0

calc_SOURCES = main.c
calc_CFLAGS = -Wall -Wextra -DLOCALEDIR=\"$(localedir)\"
calc_LDADD = libcalc.la
calc_LDFLAGS = -lm

include_HEADERS = libcalc.h
