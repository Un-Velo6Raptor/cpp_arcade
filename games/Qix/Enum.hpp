/*
** EPITECH PROJECT, 2018
** cpp_arcade
** File description:
** Created by martin.januario@epitech.eu,
*/

#ifndef CPP_ARCADE_ENUM_HPP
# define CPP_ARCADE_ENUM_HPP

namespace ar {
	enum MapPattern {
		WALKABLE = 0,
		BORDER = 3,
		NOWALKABLE = 4,
		SHARKS = 5,
		QIX = 6,
		TRAIL = 7,
		OLDBORDER = 9,
		FILLQIXTMP = 8,
		FLAME = 10,
	};

	enum DirObj {
		LEFT,
		RIGHT,
		DOWN,
		UP,
		UNKNOWN
	};
}

#endif //CPP_ARCADE_ENUM_HPP
