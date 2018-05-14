NAME = onp

SRC = onp.c
OBJ = $(SRC:.c=.o)

CFLAGS =
LDFLAGS = 

all: $(OBJ)
	gcc $(OBJ) -o $(NAME)
	
clean:
	rm -f $(OBJ)
	rm -f $(NAME)
	
re: clean all
