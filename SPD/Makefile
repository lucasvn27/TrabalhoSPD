CC = mpicc
CC1 = gcc
CFLAGS = -fopenmp
LDFLAGS = -lm -lmpi

SRC = mpi.c
SRC1 = dtwOpenMp.c

all: mpi dtwOpenMp
.PHONY: all

run: tests1 tests2
.PHONY: run

clean:
	rm -f mpi dtwOpenMp *.o

tests1: mpi
	mpiexec -v --host 10.4.0.118:2 --host 10.4.0.110:4 -np 6 ./mpi m3=600.txt n3=500.txt numeros.txt ;

tests2: dtwOpenMp
	./dtwOpenMp n3=500.txt m3=600.txt output.txt 4; 

mpi: $(SRC) Makefile
	$(CC) $(CFLAGS) $(SRC) -o $@ $(LDFLAGS)

dtwOpenMp: $(SRC1) Makefile
	$(CC1) $(CFLAGS) $(SRC1) -o $@ $(LDFLAGS)