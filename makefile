CC = gcc
CC_FLAGS = -c -O3 -Wall -Werror

DIRECTORY = directory/directory
FILE = file/file
UTILS = utils/utils

all: directory_tree

directory_tree: main.o directory.o file.o utils.o
	$(CC) main.o directory.o file.o utils.o -o main

main.o: main.c $(DIRECTORY).h $(FILE).h $(UTILS).h
	$(CC) $(CC_FLAGS) main.c -o main.o

directory.o: $(DIRECTORY).c $(DIRECTORY).h $(UTILS).h
	$(CC) $(CC_FLAGS) $(DIRECTORY).c -o directory.o

file.o: $(FILE).c $(FILE).h
	$(CC) $(CC_FLAGS) $(FILE).c -o file.o

utils.o: $(UTILS).c $(UTILS).h
	$(CC) $(CC_FLAGS) $(UTILS).c -o utils.o