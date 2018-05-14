NAME = wildbrowser

SRC = main.c print.c tagType.c request.c
OBJ = $(SRC:.c=.o)

CFLAGS = -I../../include
LDFLAGS = 

all: $(OBJ)
	gcc -L../../lib $(OBJ) -o $(NAME) -lmy -lcurses
clean:
	rm -f $(OBJ)
	rm -f $(NAME)
	
re: clean all
