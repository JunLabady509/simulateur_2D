CC = gcc
CFLAGS = -Wall -Wextra -Werror -pedantic -std=c99 `sdl-config --cflags`
LDFLAGS = `sdl-config --libs`

EXEC = mon_programme
SRC = $(wildcard *.c)
OBJ = $(SRC:.c=.o)

all: $(EXEC)


$(EXEC): $(OBJ)
		$(CC) -o $@ $^ $(LDFLAGS)

%.o: %.c 
		$(CC) -o $@ -c $< $(CFLAGS)

.PHONY: clean

clean:
		rm -rf $(OBJ) $(EXEC)

