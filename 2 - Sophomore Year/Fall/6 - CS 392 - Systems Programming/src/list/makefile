# # MAKEFILE


#  	How you should structure your directory
#
# 	->CS-392
# 		|->include
# 			|-> header files
# 		|->lib
# 			|-> compiled libraries generated from your makefile
# 		|->src
# 			|-> my
# 				|-> Makefile
# 				|-> source files
# 			|-> list
# 				|-> source files
#			|-> next assignment
#				|-> source files
# 		|->test
# 			|->Makefile
# 			|->test.c


# 	When submitting zip/rar/tar the root 392 directory.
# 	Test.c is where you should make a test main using your library

NAME = libmylist.a

SRC = new_node.c add_node.c add_elem.c append.c add_node_at.c remove_node.c\
		remove_last.c remove_node_at.c count_s_nodes.c print_string.c\
		print_int.c print_char.c node_at.c elem_at.c traverse_string.c\
		empty_list.c traverse_int.c traverse_char.c debug_int.c debug_string.c\
		debug_char.c
		

#MUST BE VERBOSE
OBJ = $(SRC:.c=.o)

CFLAGS = -I../../include -Wall -Werror -pedantic -DNDEBUG
LDFLAGS = -c

all: $(OBJ)
	ar -rc $(NAME) $(OBJ)
	ranlib $(NAME)
	mv $(NAME) ../../lib

clean:
	rm -f $(OBJ)

fclean: clean
	rm -f ../../lib/$(NAME)

re: fclean all
