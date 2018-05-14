NAME = testlist

SRC = testlist.c
OBJ = $(SRC:.c=.o)

CFLAGS = -I../include
LDFLAGS = 

all: $(OBJ)
	gcc -pedantic -L../lib $(OBJ) -o $(NAME) -lmylist -lmy

clean:
	rm -f $(OBJ)
	rm -f $(NAME)

re: clean all
