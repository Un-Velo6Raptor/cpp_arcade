##
## EPITECH PROJECT, 2018
## cpp_arcade SolarFox
## File description:
## Created by martin.januario@epitech.eu
##

SRC		=	Src/Main.cpp				\

MAP		=	Src/Map/ManageMap.cpp			\
			Src/Map/InitMap.cpp			\
			Src/Map/BasicsMap.cpp			\
			Src/Map/Map.cpp				\

GAME		=	Src/Qix/Qix.cpp			\
			Src/Qix/ManageGame.cpp			\
			Src/Qix/ManageKeyGame.cpp		\
			Src/Qix/MapGetter.cpp			\
			Src/Qix/MapRefresh.cpp			\

EXCEPTION	=	Src/Exception/ErrorException.cpp	\
			Src/Exception/MapException.cpp		\
			Src/Exception/GameException.cpp		\

OBJ		=	$(SRC:.cpp=.o)				\
			$(MAP:.cpp=.o)				\
			$(EXCEPTION:.cpp=.o)			\
			$(GAME:.cpp=.o)				\

CPPFLAGS	=	-W -Wall -Wextra -Werror		\
			-I Include/				\
			-I Include/Class/			\
			-I Include/Exception/			\
			-I Include/Interface/			\
			-I Include/Abstrat/			\

NAME		=	my_qix

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
