NAME = mysort
TARBALL = bewchy-$(NAME).tar.gz
SRC = main.cpp merge.cpp shell.cpp tools.cpp insert.cpp comparators.cpp select.cpp radix.cpp quick.cpp
OBJ = $(SRC:.cpp=.o)
RM = rm -f

all: $(OBJ)
	g++ $(OBJ) -o $(NAME)

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


