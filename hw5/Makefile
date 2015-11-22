#
# CS 11: Makefile for C track, assignment 5.
#

CC     = gcc
CFLAGS = -g -Wall -Wstrict-prototypes -ansi -pedantic

all: cellularautomaton cellularautomaton2

cellularautomaton: cellularautomaton.o memcheck.o
	$(CC) cellularautomaton.o memcheck.o -o cellularautomaton

cellularautomaton.o: cellularautomaton.c memcheck.h
	$(CC) $(CFLAGS) -c cellularautomaton.c

cellularautomaton2: cellularautomaton2.o memcheck.o
	$(CC) cellularautomaton2.o memcheck.o -o cellularautomaton2

cellularautomaton2.o: cellularautomaton2.c memcheck.h
	$(CC) $(CFLAGS) -c cellularautomaton2.c

memcheck.o: memcheck.h

check:
	./c_style_check cellularautomaton.c cellularautomaton2.c

clean:
	rm -f cellularautomaton cellularautomaton2 *.o
