SRC = $(wildcard *.c)
OBJ = $(SRC:.c=.out)
CC = gcc
CFLAGS = -g #-Wall -pedantic -O3 -std=c99 --sanitize
LDFLAGS = -lm
.PHONY: clean

all: $(OBJ)

%.out: %.c
	$(CC) $(CFLAGS) "$<" -o  "$@" $(LDFLAGS)

clean:
	rm -f $(OBJ)