CXXFLAGS = -g -std=c++17 -Wall -Wextra -Werror -Wno-unused-parameter
CXX      = g++

# These targets don't create any files:
.PHONY: all clean

# Magic Variables!
# https://www.gnu.org/software/make/manual/html_node/Automatic-Variables.html
#  $@ is the name of the target
#  $+ is a list of all the dependencies
#  $< is the first dependency

move-check: move-check.o Move.o
	${CXX} $(CXXFLAGS) -o $@ $+

move-check.o: move-check.cpp Errors.h Move.h 
	${CXX} $(CXXFLAGS) -c -o $@ $<

game-check: game-check.o Board.o Move.o
	${CXX} $(CXXFLAGS) -o $@ $+

game-check.o: game-check.cpp Board.h Move.h
	${CXX} $(CXXFLAGS) -c -o $@ $<

Board.o: Board.cpp Errors.h Board.h
	${CXX} $(CXXFLAGS) -c -o $@ $<

Move.o: Move.cpp Errors.h Move.h
	${CXX} $(CXXFLAGS) -c -o $@ $<

clean:
	/bin/rm -f *.o game-check move-check
