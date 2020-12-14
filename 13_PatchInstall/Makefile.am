bin_PROGRAMS = guess
pkgdatadir = $(localedir)/ru/LC_MESSAGES
pkgdata_DATA = ru/LC_MESSAGES/guess.mo
PROG = guess
AM_CPPFLAGS = -D LOCALEDIR='"$(localedir)"'

ru/LC_MESSAGES/guess.mo: mo

mo: $(PROG).po
	mkdir -p ru/LC_MESSAGES
	msgfmt --check --verbose --output-file=ru/LC_MESSAGES/$(PROG).mo $<

$(PROG).po: $(PROG).pot
	msgmerge -U $@ $<

$(PROG).pot: $(PROG).c
	xgettext --keyword=_ --language=C --output $(PROG).pot $(PROG).c

clean:
	rm -f ru/LC_MESSAGES/guess.mo
	rm -f guess
