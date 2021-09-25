CFLAGS?=-std=c99 -D_GNU_SOURCE -Wall -O2
CC=gcc

default: all

all: bin lab1

bin:
	mkdir -p bin/
	
lab1: findpng.c pnginfo.c crc.c
	$(CC) $(CFLAGS) -o bin/Lab1.out $<

clean:
	rm -rf bin/
