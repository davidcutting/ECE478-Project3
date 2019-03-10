CFLAGS= -g
LDFLAGS= -lpthread -lrt
LDFLAGS1= -lpthread
CC=g++

all: boundedBuffer condvar1 professorStudent

# To make an executable
boundedBuffer: boundedBuffer.o
	$(CC) $(LDFLAGS) -o boundedBuffer boundedBuffer.o

condvar1: condvar1.o
	$(CC) $(LDFLAGS1) -o condvar1 condvar1.o

professorStudent: professorStudent.o
	$(CC) $(LDFLAGS1) -o professorStudent professorStudent.o

# To make an object from source
.c.o:
	$(CC) $(CFLAGS) -c $*.c

# clean out the dross
clean:
	-rm boundedBuffer condvar1 professorStudent *.o
