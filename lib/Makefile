##
## EPITECH PROJECT, 2018
## cpp_arcade
## File description:
## Created by sahel.lucas-saoudi@epitech.eu,
##

all:
		make -C SFML
		mv SFML/*.so .

clean:
		make -C SFML clean
        
fclean:
		make -C SFML fclean
		rm -rf *.so
        
re:
		rm -rf *.so
		make -C SFML re
		mv SFML/*.so .

.PHONY: all clean fclean re