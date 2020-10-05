CC=gcc
FLAGS=-Wall
LFLAGS=-lncursesw
ENV_VARS=
OUT=Show

.PHONY: all build clean

build: clean
	$(ENV_VARS) $(CC) $(FLAGS) Show.c -o $(OUT) $(LFLAGS)

clean:
	rm -f *.o $(OUT) a.out
