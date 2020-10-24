CC=g++
g++_FLAGS=-std=c++17

all: TokenParser test

TokenParser: TokenParser.cpp
	g++ $(g++_FLAGS) TokenParser.cpp -o TokenParser

test:
	./TokenParser

clean:
	rm -f TokenParser
