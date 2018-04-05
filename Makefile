##
## EPITECH PROJECT, 2018
## arcade
## File description:
## Makefile
##

NAME		=	arcade

all:
		make -C Core
		make -C games clean
		mv ./Core/core ./$(NAME)

$(NAME):	all

clean:
		make -C Core clean
		make -C games clean
		rm -rf $(NAME)

fclean:
		make -C Core fclean
		make -C games fclean
		rm -rf $(NAME)

re:
		make -C Core re
		make -C games re
		mv ./Core/core ./$(NAME)

debug:		CXXFLAGS += -g
debug:		re



.PHONY:		all clean fclean re debug
