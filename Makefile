CC = gcc
CFLAGS = -Wall
OBJECTS = main.o

COMPILE.c=$(CC) $(CFLAGS) $(CPPFLAGS) -c

main: ${OBJECTS}

clean:
	rm ${OBJECTS} main