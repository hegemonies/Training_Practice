all: bin

bin:
	mpicc -o main main.c
	
.PHONY:

r:
	mpirun main