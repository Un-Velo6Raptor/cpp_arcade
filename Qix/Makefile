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

GAME		=	Src/Game/Game.cpp			\
			Src/Game/ManageGame.cpp			\
			Src/Game/ManageKeyGame.cpp		\
			Src/Game/GameGetter.cpp			\
			Src/Game/GameRefresh.cpp		\
			Src/Game/ManagePlayer.cpp		\

EXCEPTION	=	Src/Exception/ErrorException.cpp	\
			Src/Exception/MapException.cpp		\
			Src/Exception/GameException.cpp		\

OBJ		=	$(SRC:.cpp=.o)				\
			$(MAP:.cpp=.o)				\
			$(GAME:.cpp=.o)				\
			$(EXCEPTION:.cpp=.o)			\

CPPFLAGS	=	-std=c++11 -W -Wall -Wextra -Werror	\
			-fPIC					\
			-I Include/				\
			-I Include/Class/			\
			-I Include/Exception/			\
			-I Include/Interface/			\
			-I Include/Abstract/			\

LDFLAGS		=	-shared

NAME		=	lib_arcade_qix_martin.so

all:			$(NAME)

$(NAME):		$(OBJ)
			g++ -o $(NAME) $(OBJ) $(LDFLAGS)

clean:
			rm -f $(OBJ)

fclean:			clean
			rm -f $(NAME)

re:			fclean all

debug:			CPPFLAGS += -ggdb3

debug:			re

.PHONY:			all clean fclean re debug
