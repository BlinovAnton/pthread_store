.PHONY: clean cli

prename = pt_store_
CC = gcc
FLAGS = -Wall -g -lpthread

#vpath %.h ../include
#vpath %.c ../src

$(prename)func.o: $(prename)func.c
		$(CC) -c -o $@ $< $(FLAGS)

cli:
		rm -f *.o

clean: cli