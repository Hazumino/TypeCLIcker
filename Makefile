CC = gcc
CFLAGS = -Wall -Wextra -std=c99 -Iinclude
LDFLAGS = -lsqlite3 -lncurses -lm
SRC = $(filter-out src/sqliteSetup.c, $(wildcard src/*.c))
OBJ = $(SRC:.c=.o)
TARGET = typeclicker 

all: $(TARGET)


$(TARGET): $(OBJ)
	$(CC) -o $@ $^ $(LDFLAGS)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJ) $(TARGET)

.PHONY: clean
