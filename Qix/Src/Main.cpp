/*
** EPITECH PROJECT, 2018
** cpp_arcade
** File description:
** Created by martin.januario@epitech.eu,
*/

#include "MapException.hpp"
#include "ManageMap.hpp"
#include "Game.hpp"

int main(void)
{
	try {
		ar::Qix *game = new ar::Qix();

		game->manageKey(ar::Event::AR_PAUSE);
		int idx = 0;
		while (idx < 60) {
			if (idx <= 3)
				game->manageKey(ar::Event::AR_RIGHT);
			else if (idx <= 30)
				game->manageKey(ar::Event::AR_DOWN);
			else
				game->manageKey(ar::Event::AR_RIGHT);
//			game->_manageMap.DisplayMap();
			game->loop();
			idx++;
		}
		idx = 0;
		while (idx < 60) {
			if (idx <= 4)
				game->manageKey(ar::Event::AR_UP);
			else if (idx <= 10)
				game->manageKey(ar::Event::AR_LEFT);
			else
				game->manageKey(ar::Event::AR_UP);
//			game->_manageMap.DisplayMap();
			game->loop();
			idx++;
		}
		game->_manageMap.DisplayMap();
		delete game;
	} catch (MapException const &error) {
		std::cout << "From " << error.getName() << ":" << std::endl;
		std::cout << error.what() << std::endl;
		return 84;
	}
	return 0;
}