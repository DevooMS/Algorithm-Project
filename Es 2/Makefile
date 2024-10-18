
all: bin/edit_distance

clean:
	rm -f build/* bin/*

run: bin/edit_distance_dyn

tests: bin/edit_distance_dyn_tests

CFLAGS = -g -Wall -Wextra -Wpedantic -Wconversion

INCLUDES = src/*.h   

COMMON_DEPS = $(INCLUDES) Makefile  //include tutti i file .h

build/%.o: src/%.c $(COMMON_DEPS)
	$(CC) $(CFLAGS) -c $< -o $@

bin/edit_distance_dyn: build/edit_distance_dyn.o build/edit_distance_dyn_main.o $(COMMON_DEPS)//common_deps gli include tutti .h
	$(CC) -o bin/edit_distance_dyn build/edit_distance_dyn.o build/edit_distance_dyn_main.o

bin/edit_distance_dyn_tests: build/edit_distance_dyn_tests.o build/edit_distance_dyn.o build/unity.o $(COMMON_DEPS)
	$(CC) -o bin/edit_distance_dyn_tests  build/edit_distance_dyn_tests.o build/edit_distance_dyn.o build/unity.o

