all: lib main

build:
	mkdir -p build

heap:
	gcc -c -Iinclude src/heap.c -o build/libHeap.o -Wall

lib: heap build
	mkdir -p lib
	ar rs lib/libHeap.a build/libHeap.o
	rm -f build/libHeap.o

main: build
	gcc --static -Iinclude -Llib -o build/main src/main.c -lHeap -Wall

clean:
	rm -f build/heap lib/libHeap.a
