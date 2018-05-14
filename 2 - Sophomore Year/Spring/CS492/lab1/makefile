NAME = dp_one

SRC = dp_one.c
OBJ = $(SRC:.c=.o)

CFLAGS = 
LDFLAGS = 

all: $(OBJ)
	gcc $(OBJ) -o $(NAME) -lpthread

clean:
	rm -f $(OBJ)
	rm -f $(NAME)

re: clean all
