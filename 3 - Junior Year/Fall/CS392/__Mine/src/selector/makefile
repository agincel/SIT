NAME = selector

SRC = selector.c
OBJ = $(SRC:.c=.o)

CFLAGS = -I../../include
LDFLAGS = 

all: $(OBJ)
	gcc -L../../lib $(OBJ) -Wall -Werror --pedantic -o $(NAME) -lmy -lcurses

clean:
	rm -f $(OBJ)
	rm -f $(NAME)

re: clean all
