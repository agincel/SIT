NAME = MySBBST
TARBALL = agincel-$(NAME).tar.gz
SRC = main.cpp comparators.cpp MySBBST.cpp add.cpp remove.cpp search.cpp height.cpp order.cpp problemChecking.cpp printout.cpp 
OBJ = $(SRC:.cpp=.o)
RM = rm -f

all: $(OBJ)
	g++ -g $(OBJ) -o $(NAME)

clean:
	-$(RM) *~
	-$(RM) \#*
	-$(RM) *.o
	-$(RM) *.core

fclean:	clean
	-$(RM) $(NAME)

re: fclean all

submit: fclean
	tar cvzf $(TARBALL) *


