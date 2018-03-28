/*
** EPITECH PROJECT, 2018
** cpp_arcade
** File description:
** Created by martin.januario@epitech.eu,
*/

#include <cstdlib>
#include <ctime>
#include "ManageMap.hpp"

ManageMap::ManageMap(const unsigned int &mapSizeX, const unsigned int &mapSizeY
) : _sizeX(mapSizeX), _sizeY(mapSizeY)
{
	std::srand(std::time(nullptr));
	resetMap();
}

ManageMap::~ManageMap()
{
}

ManageMap::ManageMap(const ManageMap &other)
{
	this->_sizeX = other._sizeX;
	this->_sizeY = other._sizeY;
	this->_map = other._map;
}

ManageMap &ManageMap::operator=(ManageMap &other)
{
	this->_sizeX = other._sizeX;
	this->_sizeY = other._sizeY;
	this->_map = other._map;
	return *this;
}
