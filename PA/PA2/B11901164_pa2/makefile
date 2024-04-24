CC=g++
CFLAGS=-std=c++11 -Wall -O2

all: bin/mps

bin/mps: src/mps.cpp src/maxPlanarSubset.cpp
	mkdir -p bin
	$(CC) $(CFLAGS) src/mps.cpp src/maxPlanarSubset.cpp -o bin/mps

# clean all the .o and executable files
clean:
	rm -rf *.o lib/*.a lib/*.o bin/*

