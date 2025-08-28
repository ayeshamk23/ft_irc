CXX = g++
CXXFLAGS = -Wall -Wextra -std=c++17

SRC = main.cpp CommandDispatcher.cpp
OBJ = $(SRC:.cpp=.o)

all: ircserver

ircserver: $(OBJ)
	$(CXX) $(CXXFLAGS) -o $@ $^

clean:
	rm -f *.o ircserver
