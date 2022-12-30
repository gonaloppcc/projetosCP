CC = nvcc
BIN = bin/
SRC = src/
INCLUDES = include/
EXEC = k_means

STAT_TIMES = 3
REPORT_FILE_NAME = perf_report.txt

CFLAGS = -O3 #-fopenmp -funroll-loops -finline-functions #-std=c99

LDFLAGS = -lm

.DEFAULT_GOAL = k_means

setup:
	mkdir $(BIN)

k_means: $(SRC)k_means.cu $(BIN)utils.o
	$(CC) $(SRC)k_means.cu $(BIN)utils.o -o $(BIN)$(EXEC) $(LDFLAGS) $(CFLAGS)

$(BIN)utils.o: $(SRC)utils.cu $(INCLUDES)utils.h
	$(CC) -c $(SRC)utils.cu -o $(BIN)utils.o $(LDFLAGS) $(CFLAGS)

clean:
	rm -r bin/*

assembler: $(BIN)utils.o
	$(CC) $(CFLAGS) -S $(SRC)k_means.cu $(LDFLAGS)

run: k_means
	./$(BIN)$(EXEC)

stat: k_means
	perf stat -r $(STAT_TIMES) ./$(BIN)$(EXEC)

report: k_means
	perf record ./$(BIN)$(EXEC)
	perf report > $(REPORT_FILE_NAME)

runseq: k_means
	./$(BIN)$(EXEC) 10000000 1024

runpar: k_means
	./$(BIN)$(EXEC) 10000000 $(CP_CLUSTERS) $(THREADS)