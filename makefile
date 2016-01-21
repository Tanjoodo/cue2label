CC=g++
CFLAGS= -c -Wall --std=c++11

all: cue2label

cue2label: main.o
	$(CC) ./obj/main.o -o ./obj/cue2label

main.o: 
	$(CC) $(CFLAGS) ./src/main.cpp -o ./obj/main.o
