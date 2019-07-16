.PHONY: clean cli

prename = pt_store_
CC = gcc
FLAGS = -Wall -g -lpthread

#vpath %.h ../include
#vpath %.c ../lib

$(prename)main.o: $(prename)main.c
		$(CC) -c -o $@ $< $(FLAGS)

cli:
		rm -f *.o

clean: cli