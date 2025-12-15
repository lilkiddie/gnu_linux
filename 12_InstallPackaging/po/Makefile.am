localedir = $(datadir)/locale

MSGFMT = msgfmt
MSGMERGE = msgmerge
XGETTEXT = xgettext

POFILES = ru.po
MOFILES = $(POFILES:.po=.mo)
POTFILE = calc.pot

all: $(MOFILES)

%.mo: %.po
	$(MSGFMT) -o $@ $<

$(POTFILE): $(top_srcdir)/src/main.c
	$(XGETTEXT) --keyword=_ --language=C --add-comments --sort-output \
	  -o $@ $(top_srcdir)/src/main.c

install-data-local: $(MOFILES)
	@for mo in $(MOFILES); do \
	  lang=`basename $$mo .mo`; \
	  dir=$(DESTDIR)$(localedir)/$$lang/LC_MESSAGES; \
	  $(MKDIR_P) $$dir; \
	  $(INSTALL_DATA) $$mo $$dir/calc.mo; \
	  echo "Installing $$mo to $$dir/calc.mo"; \
	done

uninstall-local:
	@for mo in $(MOFILES); do \
	  lang=`basename $$mo .mo`; \
	  rm -f $(DESTDIR)$(localedir)/$$lang/LC_MESSAGES/calc.mo; \
	  echo "Removing $(DESTDIR)$(localedir)/$$lang/LC_MESSAGES/calc.mo"; \
	done

clean-local:
	rm -f $(MOFILES) $(POTFILE)

EXTRA_DIST = $(POFILES)
