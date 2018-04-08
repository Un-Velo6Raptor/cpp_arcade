/*
** EPITECH PROJECT, 2021
** arcade
** File description:
** Arcade class
*/

#ifndef CPP_ARCADE_ARCADE_HPP
# define CPP_ARCADE_ARCADE_HPP

#include <string>

namespace ar {
	enum Event {
		AR_UP,
		AR_DOWN,
		AR_LEFT,
		AR_RIGHT,
		AR_PREV_GRAPH_LIB,
		AR_NEXT_GRAPH_LIB,
		AR_PREV_GAME,
		AR_NEXT_GAME,
		AR_RESTART,
		AR_MENU,
		AR_EXIT,
		AR_ACTION,
		AR_PAUSE,
		AR_VALIDATE,
		AR_RESIZE,
		AR_GAME_OVER,
		AR_UNKNOWN
	};

	typedef struct userInterface {
		int score;
		std::string username;
		int time;
	} userInterface;

	typedef struct colorVector {
		unsigned char red;
		unsigned char green;
		unsigned char blue;
	} colorVector;

	typedef struct spriteCoords {
		int x;
		int y;
		int width;
		int height;
	} spriteCoords;
};

#endif //CPP_ARCADE_ARCADE_HPP
