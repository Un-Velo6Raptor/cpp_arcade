##
## EPITECH PROJECT, 2018
## cpp_arcade SolarFox
## File description:
## Created by martin.januario@epitech.eu
##

SRC		=	Src/Main.cpp				\
			../../Interfaces/Map.cpp		\

MAP		=	Src/Map/ManageMap.cpp			\
			Src/Map/InitMap.cpp			\
			Src/Map/BasicsMap.cpp			\

SHARKS		=	Src/Sharks/Sharks.cpp			\
			Src/Sharks/ManageSharks.cpp		\
			Src/Sharks/SharksIA.cpp			\

GAME		=	Src/Game/Game.cpp			\

EXCEPTION	=	Src/Exception/ErrorException.cpp	\
			Src/Exception/MapException.cpp		\
			Src/Exception/GameException.cpp		\

OBJ		=	$(SRC:.cpp=.o)				\
			$(MAP:.cpp=.o)				\
			$(SHARKS:.cpp=.o)			\
			$(GAME:.cpp=.o)				\
			$(EXCEPTION:.cpp=.o)			\

CPPFLAGS	=	-std=c++11 -W -Wall -Wextra -Werror	\
			-I Include/				\
			-I Include/Class/			\
			-I Include/Exception/			\
			-I ../../Interfaces/			\
			-I Include/Abstract/			\
			-fPIC

LDFLAGS		=	-shared

NAME		=	lib_arcade_qix.so

all:			$(NAME)

pre:
			rm -f ../../Interfaces/Map.o

$(NAME):		pre $(OBJ)
			g++ -o $(NAME) $(OBJ) $(LDFLAGS)
			cp $(NAME) ../

clean:
			rm -f $(OBJ)

fclean:			clean
			rm -f $(NAME)
			rm -f ../$(NAME)

re:			fclean all

debug:			CPPFLAGS += -ggdb3

debug:			re

.PHONY:			all clean fclean re debug pre
