NAME = pipes

SRC = pipes.c
OBJ = $(SRC:.c=.o)

CFLAGS = -I../../include
LDFLAGS =

all: $(OBJ)
	gcc -pedantic -Wall -Werror -L../../lib $(OBJ) -o $(NAME) -lmy

clean:
	rm -f $(OBJ)
	rm -f $(NAME)

re: clean all
