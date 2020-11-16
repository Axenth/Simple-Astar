NAME = astar

SRCS = src/main.cpp src/node.cpp

$INCLUDES = incl/node.hpp

OBJS := $(SRCS:.cpp=.o)

$(NAME): all

all: $(OBJS)
	clang++ -o $(NAME) $^ $(INCLUDES) -g -fsanitize=address -Ofast

%.o: %.cpp
	clang++ -o $@ -c $< $(INCLUDES)

clean:
	rm -f $(OBJS)

fclean: clean
	rm -f $(NAME)

re: fclean all