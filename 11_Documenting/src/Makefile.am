bin_PROGRAMS = number-game
number_game_SOURCES = guess.c roman.c roman.h

AM_CPPFLAGS = -DLOCALEDIR=\"$(top_builddir)/po\"

DOXYGEN_INPUT = guess.c roman.c roman.h
doc:
	doxygen ../Doxyfile
.PHONY: doc
