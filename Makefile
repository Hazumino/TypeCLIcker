CC = gcc
CFLAGS = -lsqlite3 -lncurses
LDFLAGS = -lm
SRC = $(wildcard src/main.c)
OBJ = $(SRC:.c=.o)
TARGET = typeclicker 

all:$(TARGET)

$(TARGET): $(OBJ)
	$(CC) $(CFLAGS) -o $@ $^ $(LDFLAGS)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJ) $(TARGET)

.PHONY: all clean
