# Make targets for DAVELIB "GC" Garbage Collection Utility.
# assumes GCC
# for CLANG, use:
# 'make clang'
# or,
# 'make clangd'
# for the debug-symbols build.

cc=gcc

all:	gc test

gc:		gc.c gc.h
		$(cc) -O3 -c gc.c -o gc.o

gcd:	gc.c gc.h
		$(cc) -O0 -g -DDEBUG -c gc.c -o gcd.o

test:	gc
		$(cc) gctest.c gc.o -o test.exe

testd:	gcd
		rm -f test.exe
		$(cc) -O0 -g -DDEBUG gctest.c gcd.o -o test.exe

clang:
		make gc cc=clang

clangd:
		make gcd cc=clang

test-clang:
		make test cc=clang

test-clangd:
		make testd cc=clang

clean:
	rm -f gcd.o
	rm -f gc.o
	rm -f test.exe

