CC = gcc
CFLAGS = -Wall -Wextra -Iinclude
SRC = src/main.c src/jogo.c src/terminal.c
OUT = campo_minado

all:
	$(CC) $(CFLAGS) $(SRC) -o $(OUT)

run: all
	./$(OUT)

clean:
	rm -f $(OUT)