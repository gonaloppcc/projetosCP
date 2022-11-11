CC = gcc
BIN = bin/
SRC = src/
INCLUDES = include/
EXEC = k_means

STAT_TIMES = 3
REPORT_FILE_NAME = perf_report.txt

CFLAGS = -O3 -fopenmp -funroll-loops -finline-functions -g

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

stat:
	perf stat -r $(STAT_TIMES) ./$(BIN)$(EXEC)

report:
	perf record ./$(BIN)$(EXEC)
	perf report > $(REPORT_FILE_NAME)
