##
## EPITECH PROJECT, 2018
## cpp_arcade
## File description:
## Created by sahel.lucas-saoudi@epitech.eu,
##

all:
		make -C Nibbler
		mv Nibbler/*.so .

clean:
		make -C Nibbler clean

fclean:
		make -C Nibbler fclean
		rm -rf *.so

re:
		rm -rf *.so
		make -C Nibbler re
		mv Nibbler/*.so .

.PHONY: all clean fclean re
