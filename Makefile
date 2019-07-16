.PHONY: clean cli all kek mem

prename = pt_store_
bin = main
CC = gcc
FLAGS = -Wall -g -lpthread

$(prename)func.o: $(prename)func.c
		$(CC) -c -o $@ $< $(FLAGS)

$(prename)main.o: $(prename)main.c
		$(CC) -c -o $@ $< $(FLAGS)

all: $(prename)main.o $(prename)func.o
		$(CC) -o $(bin) $^ $(FLAGS)

cli:
		rm -f *.o $(bin)

clean: cli

mem:
		valgrind --leak-check=full --show-leak-kinds=all ./$(bin)

kek: rm -f Makefile