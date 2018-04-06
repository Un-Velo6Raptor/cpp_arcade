##
## EPITECH PROJECT, 2018
## cpp_arcade
## File description:
## Created by sahel.lucas-saoudi@epitech.eu,
##

all:
		make -C SFML
		make -C NCurses
		mv SFML/*.so .
		mv NCurses/*.so .

clean:
		make -C SFML clean
		make -C NCurses clean
        
fclean:
		make -C SFML fclean
		make -C NCurses fclean
		rm -rf *.so
        
re:
		rm -rf *.so
		make -C SFML re
		make -C NCurses re
		mv SFML/*.so .
		mv NCurses/*.so .

.PHONY: all clean fclean re
