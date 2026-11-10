name = PmergeMe

CXX = c++
CXXFLAGS = -Wall -Wextra -Werror -pedantic-errors -std=c++98

SRCS = main.cpp \
	   PmergeMe
OBJS = $(SRC:.cpp=.o)
HEADERS = PmergeMe.hpp

RM = rm -f

all: $(NAME)

$(NAME): $(OBJS)
	$(CXX) $(CXXFLAGS) $(OBJS) -o $(NAME)

%.o: %.cpp $(HEADERS)
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	$(RM) $(OBJS)

fclean:
	$(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean re



