/*
** EPITECH PROJECT, 2018
** cpp_arcade
** File description:
** Created by martin.januario@epitech.eu,
*/

#include "Enum.hpp"
#include "ManageMap.hpp"

void ManageMap::DisplayMap()
{
	const std::string red("\033[0;31m");
	const std::string green("\033[1;32m");
	const std::string yellow("\033[1;33m");
	const std::string cyan("\033[0;36m");
	const std::string magenta("\033[0;35m");
	const std::string reset("\033[0m");

	for (int idx = 0; this->_map[idx]; ++idx) {
		for (int x = 0; x < this->_map.getWidth(); ++x) {
			std::cout << reset;
			switch (this->_map[idx][x]) {
			case MapPattern::QIX :
				std::cout << red;
				break;
			case MapPattern::BORDER :
				std::cout << green;
				break;
			}
			if (idx == this->_map.getPlayerY() && x == this->_map.getPlayerX())
				std::cout << reset << magenta;
			std::cout << this->_map[idx][x];
		}
		std::cout << std::endl;
	}
}