memchunk: test.o memchunk.o
	gcc -m32 test.o memchunk.o -o memchunk

memchunk.o: memchunk.c memchunk.h
	gcc -Wall -m32 -c -o memchunk.o memchunk.c 

test.o: test.c memchunk.h
	gcc -Wall -m32  -c -o test.o test.c 
