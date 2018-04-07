/*
** EPITECH PROJECT, 2018
** cpp_arcade
** File description:
** Created by martin.januario@epitech.eu,
*/

#include "MapException.hpp"
#include "ManageMap.hpp"

void ManageMap::generateFirstLine(unsigned int line)
{
	for (unsigned int idx = 0; idx < this->_sizeX; ++idx) {
		if (!idx || idx == this->_sizeX - 1)
			this->_map[line].push_back(MapChar::Corner);
		else
			this->_map[line].push_back(MapChar::Horizontal);
	}
}

void ManageMap::generateMiddleLine(unsigned int line)
{
	for (unsigned int idx = 0; idx < this->_sizeX; ++idx) {
		if (!idx || idx == this->_sizeX - 1)
			this->_map[line].push_back(MapChar::Vertical);
		else
			this->_map[line].push_back(MapChar::Empty);
	}
}

void ManageMap::createLine(unsigned int index_y)
{
	if (!index_y || index_y == this->_sizeY - 1)
		generateFirstLine(index_y);
	else
		generateMiddleLine(index_y);
}

void ManageMap::resetMap(void)
{
	if (this->_sizeX < 9 || this->_sizeY < 9)
		throw MapException("Map is to tiny, minimum (9/9)",
			"Generate Map");
	this->_map.clear();
	for (unsigned int idx_y = 0; idx_y < this->_sizeY; ++idx_y) {
		this->_map.insert({idx_y, ""});
		createLine(idx_y);
	}
}

void ManageMap::displayMap() const
{
	for (auto it = this->_map.begin(); it != this->_map.end(); ++it) {
		std::cout << "[" << it->first << "]: " << it->second
			<< std::endl;
	}
}