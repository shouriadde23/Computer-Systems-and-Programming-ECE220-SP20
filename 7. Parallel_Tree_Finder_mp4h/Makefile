CC = g++
CFLAGS = -Wall -g -std=c++11
LDFLAGS = -lpthread
DEPS = treenode.hpp tree.hpp utils.hpp make_tree.hpp

all: find_serial find_parallel

%.o: %.cpp $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS) $(LDFLAGS)

find_serial: find_serial.cpp treenode.o tree.o utils.o make_tree.o
	$(CC) -o $@ $^ $(CFLAGS) $(LDFLAGS)

find_parallel: find_parallel.cpp treenode.o tree.o utils.o make_tree.o
	$(CC) -o $@ $^ $(CFLAGS) $(LDFLAGS)

.PHONY: clean

clean:
	rm -f *.o main
