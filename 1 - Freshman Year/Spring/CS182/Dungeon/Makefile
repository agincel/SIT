NAME = Dungeon
TARBALL = agincel-$(NAME).tar.gz
SRC = main.cpp Hero.cpp Room.cpp Dungeon.cpp Hall.cpp dfs.cpp bfs.cpp mst.cpp bestPath.cpp pizzaParty.cpp raid.cpp
OBJ = $(SRC:.cpp=.o)
RM = rm -f

all: $(OBJ)
	g++ -g -Wall $(OBJ) -o $(NAME)

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


