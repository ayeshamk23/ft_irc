NAME = ircserv

SRC = Channel.cpp 
	 	 
OBJ = $(SRC:.cpp=.o)

CXX = c++

CXXFLAGS = -std=c++98 -Wall -Wextra -Werror

$(NAME): $(OBJ)
	$(CXX) $(CXXFLAGS) $(OBJ) -o $(NAME)

all: $(NAME)

clean:
	rm -rf $(OBJ)

fclean: clean
	rm -rf $(NAME)

re: fclean allCXX = g++
CXXFLAGS = -Wall -Wextra -std=c++17

SRC = main.cpp CommandDispatcher.cpp
OBJ = $(SRC:.cpp=.o)

all: ircserver

ircserver: $(OBJ)
	$(CXX) $(CXXFLAGS) -o $@ $^

clean:
	rm -f *.o ircserver
