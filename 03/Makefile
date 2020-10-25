CC=g++
g++_FLAGS=-std=c++17

all: Matrix test

Matrix: Matrix.cpp
	g++ $(g++_FLAGS) Matrix.cpp -o Matrix

test:
	./Matrix

clean:
	rm -f Matrix
