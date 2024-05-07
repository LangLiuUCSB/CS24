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

test: test.o AST.o Stack.o Nodes.o
	${CXX} $(CXXFLAGS) -o $@ $+

test.o: test.cpp AST.h
	${CXX} $(CXXFLAGS) -c -o $@ $<

AST.o: AST.cpp AST.h Nodes.h
	${CXX} $(CXXFLAGS) -c -o $@ $<

Stack.o: Stack.cpp Stack.h
	${CXX} $(CXXFLAGS) -c -o $@ $<

Nodes.o: Nodes.cpp Nodes.h
	${CXX} $(CXXFLAGS) -c -o $@ $<

clean:
	rm -f test *.o