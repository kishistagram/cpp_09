NAME = RPN

CXX = c++
CXXFLAGS = -Wall -Wextra -Werror -pedantic-errors -std=c++98
INCLUDE = -I .

SRC = main.cpp \
	  RPN.cpp

OBJS = $(SRC:.cpp=.o)

RM = rm -f

all : $(NAME)

$(NAME): $(OBJS)
	$(CXX) $(CXXFLAGS) $(OBJS) -o $(NAME)

%.o: %.cpp RPN.hpp
	$(CXX) $(CXXFLAGS) $(INCLUDE) -c $< -o $@

clean:
	$(RM) $(OBJS)

fclean: clean
	$(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean re