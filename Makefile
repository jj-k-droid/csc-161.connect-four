CC := clang
CFLAGS := -g -Wall

all: game

clean:
	rm -rf game game.dSYM

game: game.c
	$(CC) $(CFLAGS) -o game game.c

.PHONY: all clean
