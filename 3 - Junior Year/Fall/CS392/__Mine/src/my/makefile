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
# 			|-> next assignment
# 				|-> source files
# 		|->test
# 			|->Makefile
# 			|->test.c


# 	When submitting zip/rar/tar the root 392 directory.
# 	Test.c is where you should make a test main using your library

NAME = libmy.a

SRC = my_char.c my_str.c my_digits.c my_alpha.c my_int.c my_find.c\
	my_rfind.c my_strlen.c my_revstr.c my_num_base.c\
	my_strindex.c my_strrindex.c my_strcmp.c my_strncmp.c my_strcat.c my_strconcat.c\
	my_strcpy.c my_strncpy.c my_strdup.c my_strnconcat.c my_vect2str.c my_str2vect.c my_atoi.c

#MUST BE VERBOSE
OBJ = $(SRC:.c=.o)

CFLAGS = -I../../include -Wall -Werror --pedantic
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
