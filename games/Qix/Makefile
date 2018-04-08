##
## EPITECH PROJECT, 2018
## cpp_arcade SolarFox
## File description:
## Created by martin.januario@epitech.eu
##

SRC		=	../../Interfaces/Map.cpp		\
			ManageMap.cpp	\
			Sharks.cpp


OBJ		=	$(SRC:.cpp=.o)

CPPFLAGS	=	-std=c++11 -W -Wall -Wextra -Werror	\
			-I .	\
			-I ../../Interfaces/			\
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
