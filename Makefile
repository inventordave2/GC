# Make targets for DAVELIB "GC" Garbage Collection Utility.
# assumes GCC
# for CLANG, use:
# 'make clang'
# or,
# 'make clangd'
# for the debug-symbols build.

cc=gcc

all: gc

gc: gc.c gc.h
	$(cc) -O3 -c gc.c -o gc.o

gcd: gc.c gc.h
	$(cc) -O0 -g -DDEBUG -c gc.c -o gcd.o

clang:
	make gc cc=clang

clangd:
	make gcd cc=clang

clean:
	rm -f gcd.o
	rm -f gc.o

