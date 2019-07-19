.PHONY: clean cli all kek debug mem

prename = pt_store_
bin = main
CC = gcc
FLAGS = -Wall -g -lpthread
SDIR = src
LDIR = lib
DIRS = $(SDIR) $(LDIR)

vpath %.o $(SDIR) : $(LDIR)

all: $(prename)func.o $(prename)main.o
		$(CC) -o $(bin) $^ $(FLAGS)
		strip $(bin)

debug: $(prename)func.o $(prename)main.o
		$(CC) -o $(bin) $^ $(FLAGS)

$(prename)func.o:
		make -C $(LDIR)

$(prename)main.o:
		make -C $(SDIR)

cli:
		rm -f $(SDIR)/*.o
		rm -f $(LDIR)/*.o
		rm -f $(bin)

clean: cli

mem:
		valgrind --leak-check=full --show-leak-kinds=all ./$(bin)

kek: rm -f Makefile