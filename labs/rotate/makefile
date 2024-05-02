CXXFLAGS = -g -std=c++17 -Wall -Wextra -Werror -Wno-unused-parameter
CXX      = g++

# These targets don't create any files:
.PHONY: all clean

# Magic Variables!
# https://www.gnu.org/software/make/manual/html_node/Automatic-Variables.html
#  $@ is the name of the target
#  $+ is a list of all the dependencies
#  $< is the first dependency

all: test
	./test

test: test.o Tree.o Node.o
	${CXX} $(CXXFLAGS) -o $@ $+

test.o: test.cpp Tree.h
	${CXX} $(CXXFLAGS) -c -o $@ $<

Tree.o: Tree.cpp Tree.h
	${CXX} $(CXXFLAGS) -c -o $@ $<

Node.o: Node.cpp Node.h
	${CXX} $(CXXFLAGS) -c -o $@ $<

clean:
	rm -f test test.o Tree.o Node.o