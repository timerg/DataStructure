C = gcc
FLAGS = -Wall -g
LIB = ~/GitHub/DataStructure/LIB/linked.o
OBJ = main.o hash.o $(LIB)


all: main


main: main.o hash.o $(LIB)
	$(C) $(FLAGS) $(OBJ) -o main

main.o: main.c

hash.o: hash.c $(LIB)

clean:
	rm -f *~ *.o main



  # make can't see anything in the file for object.o,
  # but it does see an object.c file,
  # and it knows how to turn a .c into a .o, so it does that.
# http://stackoverflow.com/questions/13664693/makefile-compiling-and-linking
# http://mrbook.org/blog/tutorials/make/