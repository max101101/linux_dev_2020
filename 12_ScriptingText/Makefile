CFLAGS = -Wall -std=c99
LDFLAGS = -lglib-2.0

.PHONY: all clean

PROG = count_words

all: $(PROG)

$(PROG): $(PROG).c $(PROG).h
	$(CC) -I /usr/local/opt/glib/include/glib-2.0 -I /usr/local/opt/glib/lib/glib-2.0/include/ $(CFLAGS) -o $@ $< $(LDFLAGS)
	
clean:
	rm -f $(PROG)
