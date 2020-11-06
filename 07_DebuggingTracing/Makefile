.PHONY: all build test clean

all: build test clean

build:
	gcc -Wall -shared -fPIC -ldl -o lib.so lib.c

clean:
	rm -f lib.so file1 fileFIX1 file2 FIXfile2

test:
	touch file1
	touch fileFIX1
	touch file2
	touch FIXfile2
	-rm ./file1
	-rm ./fileFIX1
	-LD_PRELOAD=$(shell pwd)/lib.so rm ./file2
	-LD_PRELOAD=$(shell pwd)/lib.so rm ./FIXfile2
	@if [ -f file1 ]; then \
		echo 'Error: file1 was not deleted'; \
		exit 1; \
	fi
	@if [ -f fileFIX1 ]; then \
		echo 'Error: fileFIX1 was not deleted'; \
		exit 1; \
	fi
	@if [ -f file2 ]; then \
		echo 'Error: file2 was not deleted'; \
		exit 1; \
	fi
	@if [ ! -f FIXfile2 ]; then \
		echo 'Error: FIXfile2 was deleted'; \
		exit 1; \
	fi
