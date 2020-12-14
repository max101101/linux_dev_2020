CFLAGS = -Wall -std=c99
LDFLAGS = -lintl

PROG = guess

.PHONY: all clean

all: $(PROG) mo

$(PROG): $(PROG).c
	$(CC) $(CFLAGS) -o $@ $< $(LDFLAGS)

mo: $(PROG).po
	mkdir -p ./ru_RU.utf8/LC_MESSAGES
	msgfmt --check --verbose --output-file=ru_RU.utf8/LC_MESSAGES/$(PROG).mo $<

$(PROG).po: $(PROG).pot
	msgmerge -U $@ $<

$(PROG).pot: $(PROG).c
	xgettext --keyword=_ --language=C --output $(PROG).pot $(PROG).c

clean:
	@rm -f $(PROG)
	@rm -r ru_RU.utf8/
