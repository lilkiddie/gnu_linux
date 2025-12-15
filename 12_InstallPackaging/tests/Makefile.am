TESTS = test_calc
check_PROGRAMS = test_calc

test_calc_SOURCES = test_calc.c
test_calc_CFLAGS = -I$(top_srcdir)/src -Wall -Wextra
test_calc_LDADD = $(top_builddir)/src/libcalc.la
test_calc_LDFLAGS = -lm
