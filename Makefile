##
## EPITECH PROJECT, 2019
## 203hotline_2018
## File description:
## Makefile
##

SRC	=	main.cpp	

NAME	=	server

OBJ	=	$(SRC:.cpp=.o)

all	:	$(NAME)

$(NAME)	:	$(OBJ)
	g++ -o $(NAME) $(SRC) -g -Wall -Wextra 
clean:
	rm -rf $(OBJ)

re	:	fclean all

fclean	: clean
	rm -rf $(NAME) *.o *~ *.gcda *.gcno *# 
