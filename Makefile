##
## EPITECH PROJECT, 2018
## arcade
## File description:
## Makefile
##

CXX		=	g++

NAME		=	lib_arcade_nibbler.so

SRC		=	Src/Map.cpp \
			Src/Snake.cpp

OBJ		=	$(SRC:.cpp=.o)

CPPFLAGS	=	-W -Wall -Wextra -I./Include -std=c++11 -fPIC

LDFLAGS		=	-shared

all:		$(NAME)

$(NAME):	$(OBJ)
	$(CXX) -o $(NAME) $(OBJ) $(LDFLAGS)

clean:
	rm -f $(OBJ)

fclean:		clean
	rm -f $(NAME)

re:		fclean all

rec:		all clean

debug:		CPPFLAGS += -g
debug:		re

.PHONY:		all clean fclean re rec debug
