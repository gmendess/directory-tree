CC = gcc
CC_FLAGS = -c -O3 -Wall -Werror

DIRECTORY = directory/directory
FILE = file/file

all: directory_tree

directory_tree: main.o directory.o file.o
	$(CC) main.o directory.o file.o -o main

main.o: main.c $(DIRECTORY).h $(FILE).h
	$(CC) $(CC_FLAGS) main.c -o main.o

directory.o: $(DIRECTORY).c $(DIRECTORY).h
	$(CC) $(CC_FLAGS) $(DIRECTORY).c -o directory.o

file.o: $(FILE).c $(FILE).h
	$(CC) $(CC_FLAGS) $(FILE).c -o file.o