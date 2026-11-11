NAME = PmergeMe

CXX = c++
CXXFLAGS = -Wall -Wextra -Werror -pedantic-errors -std=c++98

DEBUG ?= 0

ifeq ($(DEBUG),1)
	CXXFLAGS += -DPMERGEME_DEBUG
endif

SRCS = main.cpp \
	   PmergeMe.cpp \
	   ComparisonReport.cpp

OBJS = $(SRCS:.cpp=.o)

HEADERS = PmergeMe.hpp \
		  ComparisonReport.hpp

RM = rm -f

all: $(NAME)

$(NAME): $(OBJS)
	$(CXX) $(CXXFLAGS) $(OBJS) -o $(NAME)

%.o: %.cpp $(HEADERS)
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	$(RM) $(OBJS)

fclean: clean
	$(RM) $(NAME)

re: fclean all

debug: $(MAKE) re DEBUG=1


.PHONY: all clean fclean re



