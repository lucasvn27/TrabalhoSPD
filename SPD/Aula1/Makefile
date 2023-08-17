# makefile para exercicios de OpenMP

CC = gcc
CFLAGS = -Wall -std=gnu99
LDFLAGS = -lm -fopenmp

SRC1 = exemplo1.c
SRC2 = exemplo2.c
SRC3 = exemplo-ambiente.c

all: exemplo1 exemplo2 exemplo-ambiente
.PHONY: all

run:	tests1 tests2 tests3
.PHONY: run


clean:	
	rm exemplo1 exemplo2 exemplo-ambiente *.o


tests1:	exemplo1
	export OMP_NUM_THREADS=4; ./exemplo1
	export OMP_NUM_THREADS=5; ./exemplo1

tests2:	exemplo2
	export OMP_NUM_THREADS=4; ./exemplo2
	export OMP_NUM_THREADS=5; ./exemplo2

tests3:	exemplo-ambiente
	export OMP_NUM_THREADS=4; ./exemplo-ambiente
	export OMP_NUM_THREADS=5; ./exemplo-ambiente

exemplo1:	$(SRC1) Makefile
	$(CC) $(CFLAGS) $(SRC1) $(LDFLAGS) -o $@

exemplo2:	$(SRC2) Makefile
	$(CC) $(CFLAGS) $(SRC2) $(LDFLAGS) -o $@

exemplo-ambiente:	$(SRC3) Makefile
	$(CC) $(CFLAGS) $(SRC3) $(LDFLAGS) -o $@
