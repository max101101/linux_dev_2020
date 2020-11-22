CFLAGS = -Wall -std=c99
LDFLAGS = -lintl

PROG = guess

.PHONY: all clean

all: $(PROG) docs gen-man mo

$(PROG): $(PROG).c
	$(CC) $(CFLAGS) -o $@ $< $(LDFLAGS)

mo: $(PROG).po
	mkdir -p ./ru_RU.utf8/LC_MESSAGES
	msgfmt --check --verbose --output-file=ru_RU.utf8/LC_MESSAGES/$(PROG).mo $<

$(PROG).po: $(PROG).pot
	msgmerge -U $@ $<

$(PROG).pot: $(PROG).c
	xgettext --keyword=_ --language=C --output $(PROG).pot $(PROG).c

docs:
	doxygen doxyconf.txt

man: gen-man
	man ./man/$(PROG)

gen-man: $(PROG)
	mkdir -p ./man
	LC_ALL=C help2man -n $(PROG) --no-discard-stderr ./$(PROG) > ./man/$(PROG)

clean:
	@rm -f $(PROG)
	@rm -r ru_RU.utf8/
