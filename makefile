CC = gcc
CFLAGS = -I./inc -Wall -Wextra -O2 -march=native

INC = $(wildcard inc/*.h)
SRC = src/main.c
OBJ = $(SRC:.c=.o)

BIN = hangman

all: $(BIN)

clean:
	rm -f $(OBJ) $(BIN)

%.o: %.c $(INC)
	$(CC) $(CFLAGS) -c -o $@ $<

$(BIN): $(OBJ)
	$(CC) -o $@ $^
