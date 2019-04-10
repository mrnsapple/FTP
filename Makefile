##
## EPITECH PROJECT, 2019
## 203hotline_2018
## File description:
## Makefile
##

SRC	=	main.c					\
		child.c					\
		read.c					\
		send.c					\
		my_str_to_word_tab.c	\
		pwd/get_pwd.c

NAME	=	myftp

OBJ	=	$(SRC:.c=.o)

all	:	$(NAME)

$(NAME)	:	$(OBJ)
	gcc -o $(NAME) $(SRC) -g -Wall -Wextra 
clean:
	rm -rf $(OBJ)

re	:	fclean all

fclean	: clean
	rm -rf $(NAME) *.o *~ *.gcda *.gcno *# .vscode
