/*
** EPITECH PROJECT, 2018
** cpp_arcade
** File description:
** Created by martin.januario@epitech.eu,
*/

#ifndef CPP_ARCADE_ENUM_HPP
# define CPP_ARCADE_ENUM_HPP

enum DirectionObj {
	UNKNOWN,
	LEFT,
	RIGHT,
	DOWN,
	UP
};

enum MapChar {
	Empty = ' ',
	Corner = '+',
	Vertical = '|',
	Horizontal = '-',
	ObjectToTake = 'o',
};

#endif //CPP_ARCADE_ENUM_HPP
