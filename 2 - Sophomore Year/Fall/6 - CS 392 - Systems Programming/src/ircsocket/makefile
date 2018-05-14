NAME = server
NAME2 = client

SRC1 = server.c
OBJ1 = $(SRC1:.c=.o)

SRC2 = client.c
OBJ2 = $(SRC2:.c=.o)

CFLAGS = -I../../include
LDFLAGS =

all: server client

server: $(OBJ1)
	gcc -pedantic -Wall -Werror -L../../lib $(OBJ1) -o $(NAME) -lmylist -lmy

client: $(OBJ2)
	gcc -pedantic -Wall -Werror -L../../lib $(OBJ2) -o $(NAME2) -lmylist -lmy

clean:
	rm -f $(OBJ1)
	rm -f $(NAME)
	rm -f $(OBJ2)
	rm -f $(NAME2)

re: clean all
