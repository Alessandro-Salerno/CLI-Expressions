CC = gcc
CFLAGS = -Wextra -Wall
LFLAGS = -lm
SRC = src/cliexp.c
OBJS = tmp/cliexp.o
BIN = bin/cliexp

$(OBJS): $(SRC)
	$(CC) $(CFLAGS) -c $^ -o $@


cliexp: $(OBJS) link

link:
	$(CC) $(LFLAGS) $(SRC) -o $(BIN)

setup:
	@ mkdir bin
	@ mkdir tmp
