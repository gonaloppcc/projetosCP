CC = gcc
BIN = bin/
SRC = src/
INCLUDES = include/
EXEC = k_means

CFLAGS = -O3 -funroll-loops -finline-functions

LDFLAGS = -lm

.DEFAULT_GOAL = k_means

setup:
	mkdir $(BIN)

k_means: $(SRC)k_means.c $(BIN)utils.o
	$(CC) $(SRC)k_means.c $(BIN)utils.o -o $(BIN)$(EXEC) $(LDFLAGS) $(CFLAGS)

$(BIN)utils.o: $(SRC)utils.c $(INCLUDES)utils.h
	$(CC) -c $(SRC)utils.c -o $(BIN)utils.o $(LDFLAGS) $(CFLAGS)

clean:
	rm -r bin/*

assembler: $(BIN)utils.o
	$(CC) $(CFLAGS) -S $(SRC)k_means.c $(LDFLAGS)

run: k_means
	./$(BIN)$(EXEC)