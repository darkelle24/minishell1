##
## EPITECH PROJECT, 2018
## Makefile
## File description:
## Makefile
##

CC	=	gcc

SRC	=	src/main.c					\
		src/my_strcmp.c				\
		src/create_env.c 			\
		src/fcfind.c				\
		src/my_strlen.c

OBJ	=	$(SRC:.c=.o)

NAME	=	mysh

RULE =	--no-print-directory

all:	$(NAME)

$(NAME):	$(OBJ)
	$(CC) -o $(NAME) $(OBJ)

spe:	fclean
	make $(RULE) all CFLAGS=-ggdb

clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME)

re:	fclean all

.PHONY: all clean fclean re spe
