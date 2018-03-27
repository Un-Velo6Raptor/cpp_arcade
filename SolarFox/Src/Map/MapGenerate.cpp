/*
** EPITECH PROJECT, 2018
** cpp_arcade
** File description:
** Created by martin.januario@epitech.eu,
*/

#include "MapException.hpp"
#include "ManageMap.hpp"

void ManageMap::generateMap(void)
{
	if (this->_sizeX < 9 || this->_sizeY < 9)
		throw MapException("Map is to tiny, minimum (9/9)",
			"Generate Map");
	std::cout << "The map is generated" << std::endl;
}