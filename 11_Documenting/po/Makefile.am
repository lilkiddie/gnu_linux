POTFILES = ../src/guess.c ../src/roman.c

messages.pot: $(POTFILES)
	xgettext --keyword=_ --language=C --output=messages.pot $(POTFILES)

ru/LC_MESSAGES/guess.mo: ru.po
	mkdir -p $(dir $@)
	msgfmt ru.po -o $@

pkgdatadir = $(datadir)
pkgdata_DATA = ru/LC_MESSAGES/guess.mo

CLEANFILES = messages.pot ru/LC_MESSAGES/guess.mo
