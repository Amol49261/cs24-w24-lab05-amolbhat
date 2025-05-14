CXX      = g++
CXXFLAGS = -g --std=c++20 -Wall

all: game game_set tests

# -------------------
# STL‐set version
game_set: card.o main_set.o
	$(CXX) $(CXXFLAGS) card.o main_set.o -o game_set

# BST‐based version (now includes card.o)
game: card_list.o main.o card.o
	$(CXX) $(CXXFLAGS) card_list.o main.o card.o -o game

# Test harness
tests: card.o card_list.o tests.o
	$(CXX) $(CXXFLAGS) card.o card_list.o tests.o -o tests

# -------------------
# Compile rules
main_set.o: main_set.cpp
	$(CXX) $(CXXFLAGS) -c main_set.cpp

main.o: main.cpp
	$(CXX) $(CXXFLAGS) -c main.cpp

tests.o: tests.cpp
	$(CXX) $(CXXFLAGS) -c tests.cpp

card_list.o: card_list.cpp card_list.h
	$(CXX) $(CXXFLAGS) -c card_list.cpp

card.o: card.cpp card.h
	$(CXX) $(CXXFLAGS) -c card.cpp

# -------------------
clean:
	rm -f *.o game game_set tests

