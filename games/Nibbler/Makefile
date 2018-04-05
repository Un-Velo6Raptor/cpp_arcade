##
## EPITECH PROJECT, 2018
## cpp_arcade
## File description:
## Created by sahel.lucas-saoudi@epitech.eu,
##

SRC     =       Snake.cpp	\
				../../Interfaces/Map.cpp

CXXFLAGS  =   -W -Wall -Wextra -I . -I ../../Interfaces -std=c++11 -fPIC

LDFLAGS	=	-shared

OBJ     =   $(SRC:.cpp=.o)

NAME		=	lib_arcade_nibbler.so

all:    $(NAME)

pre:
		rm -rf ../../Interfaces/Map.o

$(NAME):    pre $(OBJ)
		g++ -o $(NAME) $(OBJ) $(LDFLAGS)

clean:
		rm -rf $(OBJ)
        
fclean: clean
		rm -rf $(NAME)
        
re:     fclean all

debug:	CXXFLAGS += -g

debug:	re

.PHONY: all $(NAME) clean fclean re debug pre