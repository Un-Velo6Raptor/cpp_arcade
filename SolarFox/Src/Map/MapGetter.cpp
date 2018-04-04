/*
** EPITECH PROJECT, 2018
** cpp_arcade
** File description:
** Created by martin.januario@epitech.eu,
*/

#include "ManageMap.hpp"

unsigned int ManageMap::getSizeY() const
{
	return this->_sizeY;
}

unsigned int ManageMap::getSizeX() const
{
	return this->_sizeX;
}

std::map<unsigned int, std::string>& ManageMap::getMap()
{
	return this->_map;
}