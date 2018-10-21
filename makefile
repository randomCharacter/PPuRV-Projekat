CC=gcc
LDIR=lib
IDIR=include
BDIR=build

all: lib main

build:
	mkdir -p $(BDIR)

heap:
	$(CC) -c -I$(IDIR) src/heap.c -o $(BDIR)/libHeap.o -Wall

lib: heap build
	mkdir -p $(LDIR)
	ar rs $(LDIR)/libHeap.a $(BDIR)/libHeap.o
	rm -f $(BDIR)/libHeap.o

main: build
	$(CC) --static -I$(IDIR) -L$(LDIR) -o $(BDIR)/main src/main.c -lHeap -Wall

clean:
	rm -f $(BDIR)/heap $(LDIR)/libHeap.a
