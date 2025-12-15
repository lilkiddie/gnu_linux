if HAVE_DOXYGEN

all-local:
	$(DOXYGEN) Doxyfile

install-data-local:
	if test -d html; then \
	  $(MKDIR_P) $(DESTDIR)$(datadir)/doc/$(PACKAGE)/html; \
	  cp -r html/* $(DESTDIR)$(datadir)/doc/$(PACKAGE)/html/; \
	fi

uninstall-local:
	rm -rf $(DESTDIR)$(datadir)/doc/$(PACKAGE)/html

clean-local:
	rm -rf html latex

endif

EXTRA_DIST = Doxyfile
