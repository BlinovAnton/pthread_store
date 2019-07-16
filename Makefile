.PHONY: clean cli all kek mem

prename = pt_store_
bin = main
CC = gcc
FLAGS = -Wall -g -lpthread
SDIR = src
LDIR = lib
DIRS = $(SDIR) $(LDIR)

#vpath %.h ./include
#VPATH %.o $(SDIR) : $(LDIR)
#vpath %.o $(LDIR) : $(SDIR)
#vpath %.c $(SDIR) : $(LDIR)

#i'm not stupid, told you, vpath isn't working

SHIT = $(SDIR)/$(prename)main.o $(LDIR)/$(prename)func.o

$(prename)funk.o:
		make -C $(LDIR)

$(prename)main.o:
		make -C $(SDIR)

all: $(prename)funk.o $(prename)main.o
		$(CC) -o $(bin) $(SHIT) $(FLAGS)

cli:
		rm -f $(SDIR)/*.o
		rm -f $(LDIR)/*.o
		rm -f $(bin)

clean: cli

mem:
		valgrind --leak-check=full --show-leak-kinds=all ./$(bin)

kek: rm -f Makefile