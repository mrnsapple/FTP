##
## EPITECH PROJECT, 2019
## 203hotline_2018
## File description:
## Makefile
##

SRC	=	main.c	

NAME	=	server

OBJ	=	$(SRC:.c=.o)

all	:	$(NAME)

$(NAME)	:	$(OBJ)
	gcc -o $(NAME) $(SRC) -g -Wall -Wextra 
clean:
	rm -rf $(OBJ)

re	:	fclean all

fclean	: clean
	rm -rf $(NAME) *.o *~ *.gcda *.gcno *# 
