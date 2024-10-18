
all: bin/binary_insertion_sort bin/binary_insertion_sort_tests

clean:
	rm -f build/* bin/*

run: bin/binary_insertion_sort

tests: bin/binary_insertion_sort_tests

CFLAGS = -g -Wall -Wextra -Wpedantic -Wconversion

INCLUDES = src/*.h

COMMON_DEPS = $(INCLUDES) Makefile

build/%.o: src/%.c $(COMMON_DEPS)
	$(CC) $(CFLAGS) -c $< -o $@

bin/binary_insertion_sort: build/binary_insertion_sort.o build/binary_insertion_sort_main.o $(COMMON_DEPS)
	$(CC) -o bin/binary_insertion_sort build/binary_insertion_sort.o build/binary_insertion_sort_main.o

bin/binary_insertion_sort_tests: build/binary_insertion_sort_tests.o build/binary_insertion_sort.o build/unity.o $(COMMON_DEPS)
	$(CC) -o bin/binary_insertion_sort_tests  build/binary_insertion_sort_tests.o build/binary_insertion_sort.o build/unity.o


