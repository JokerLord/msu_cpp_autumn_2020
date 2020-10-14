CC=g++
g++_FLAGS=-std=c++17
valgrind_FLAGS=--tool=memcheck --leak-check=yes --show-reachable=yes --num-callers=20 --track-fds=yes -s

all: Allocator test

Allocator: Allocator.cpp
	g++ $(g++_FLAGS) Allocator.cpp -o Allocator

test: Allocator.cpp
	valgrind $(valgrind_FLAGS) ./Allocator

clean:
	rm -f Allocator
