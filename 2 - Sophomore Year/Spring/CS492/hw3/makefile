NAME = hw3

SRC = hw3.cpp g_node.cpp l_node.cpp helpers.cpp f_node.cpp

OBJ = $(SRC:.cpp=.o)

all: $(OBJ)
	g++ $(OBJ) -o $(NAME) -lpthread
	rm -f $(OBJ)

clean:
	rm -f $(NAME)
	rm -f $(OBJ)

re: clean all
