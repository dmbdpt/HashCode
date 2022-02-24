SRC = $(filter-out main.cpp,$(wildcard *.cpp))
OBJ = $(SRC:.cpp=.o)
CC = g++
CFLAGS = -g -O3 #-Wall -pedantic -O3 -std=c99 --sanitize
LINKERFLAG=-c
LDFLAGS =
.PHONY: clean

all: $(OBJ)
	-$(CC) $(CFLAGS) main.cpp $(OBJ) -o main

%.o: %.cpp
	-$(CC) $(CFLAGS) $(LINKERFLAG)  "$<" -o  "$@" $(LDFLAGS)

clean:
	-rm -f $(OBJ) main