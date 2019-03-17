CFLAGS= -g
LDFLAGS= -lpthread -lrt
LDFLAGS1= -lpthread
CC=g++

all: boundedBuffer professorStudent onelanebridge

# To make an executable
boundedBuffer: boundedBuffer.o
	$(CC) $(LDFLAGS) -o boundedBuffer boundedBuffer.o

professorStudent: professorStudent.o
	$(CC) $(LDFLAGS1) -o professorStudent professorStudent.o

onelanebridge: onelanebridge.o
	$(CC) $(LDFLAGS1) -o onelanebridge onelanebridge.o

# To make an object from source
.c.o:
	$(CC) $(CFLAGS) -c $*.c

# clean out the dross
clean:
	-rm boundedBuffer condvar1 professorStudent onelanebridge *.o
