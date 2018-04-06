##
## EPITECH PROJECT, 2018
## arcade
## File description:
## Makefile
##

NAME		=	arcade

all:	core games # TODO add lib

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

core:
	make -C Core
	mv Core/core $(NAME)

games:
	make -C games

graphicals:
	make -C lib

.PHONY:		all clean fclean re debug core graphicals games
