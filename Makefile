CC=gcc
CPPFLAGS=
CFLAGS= -std=c99 -Wall -pedantic -Iinclude
LDFLAGS= -lncurses

all: src/*
	$(CC) $^ $(CFLAGS) $(LDFLAGS) -o bin/obstruction

clean: 
	rm bin/*
	rm resources/.scoreboard