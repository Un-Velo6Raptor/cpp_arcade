##
## EPITECH PROJECT, 2018
## cpp_arcade
## File description:
## Created by sahel.lucas-saoudi@epitech.eu,
##

SRC		=	Config.cpp				\
			Core.cpp				\
			DLoader.cpp				\
			main.cpp				\
			../Interfaces/Map.cpp

OBJ		=	$(SRC:.cpp=.o)

NAME	=	core

CXXFLAGS	=	-W -Wall -Wextra -I ../Interfaces -I . -std=c++11

LIB		=	-ldl

all:	$(NAME)

$(NAME):	$(OBJ)
	g++ -o $(NAME) $(OBJ) $(LIB)

clean:
	rm -rf $(OBJ)

fclean: clean
	rm -rf $(NAME)

re:		fclean all

debug:	CXXFLAGS += -g

debug: re

.PHONY: $(NAME) all clean fclean re debug