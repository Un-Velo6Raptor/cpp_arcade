##
## EPITECH PROJECT, 2018
## cpp_arcade SolarFox
## File description:
## Created by martin.januario@epitech.eu
##

SRC		=	Src/Main.cpp				\

MAP		=	Src/Map/ManageMap.cpp			\
			Src/Map/MapGenerate.cpp			\
			Src/Map/MapGetter.cpp			\
			Src/Map/MapSetter.cpp			\

EXCEPTION	=	Src/Exception/ErrorException.cpp	\
			Src/Exception/MapException.cpp		\

OBJ		=	$(SRC:.cpp=.o)				\
			$(MAP:.cpp=.o)				\
			$(EXCEPTION:.cpp=.o)			\

CPPFLAGS	=	-W -Wall -Wextra -Werror		\
			-I Include/				\
			-I Include/Class/			\
			-I Include/Exception/			\

NAME		=	SolarFox

all:			$(NAME)

$(NAME):		$(OBJ)
			g++ -o $(NAME) $(OBJ)

clean:
			rm -f $(OBJ)

fclean:			clean
			rm -f $(NAME)

re:			fclean all

debug:			CPPFLAGS += -ggdb3

debug:			re

.PHONY:			all clean fclean re debug
