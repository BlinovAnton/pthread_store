name = pt_store
CC = gcc
FLAGS = -g -lpthread

all:
		$(CC) -Wall -o $(name) $(name).c $(FLAGS)

cli:
		rm -f $(name).o $(name)

clean: cli