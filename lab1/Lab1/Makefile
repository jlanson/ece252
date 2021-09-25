CFLAGS?=-std=c99 -D_GNU_SOURCE -Wall -O2
CC=gcc

default: all

all: bin findpng pnginfo catpng 

bin:
	mkdir -p bin/
	
findpng: findpng.c 
	$(CC) $(CFLAGS) -o bin/findpng.out $<

pnginfo: pnginfo.c crc.c 
	$(CC) $(CFLAGS) -o bin/pnginfo.out crc.c $<

catpng: findpng.c
	$(CC) $(CFLAGS) -o bin/catpng.out $<

clean:
	rm -rf bin/
