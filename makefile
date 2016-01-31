CC=g++
override CFLAGS+=-c -Wall --std=c++11

all: cue2label

cue2label: main.o interpreter.o
	$(CC) ./obj/main.o ./obj/interpreter.o -o ./obj/cue2label

main.o: 
	$(CC) $(CFLAGS) ./src/main.cpp -o ./obj/main.o

interpreter.o:
	$(CC) $(CFLAGS) ./src/interpreter.cpp -o ./obj/interpreter.o
