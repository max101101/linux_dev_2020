CFLAGS = -Wall -std=c99
LDFLAGS = -lglib-2.0

.PHONY: all clean

PROG = count_words

all: $(PROG)

$(PROG): $(PROG).c
	$(CC) $(CFLAGS) -o $@ $< $(LDFLAGS)
	
clean:
	rm -f $(PROG)
