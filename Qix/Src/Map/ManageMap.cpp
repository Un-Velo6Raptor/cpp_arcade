/*
** EPITECH PROJECT, 2018
** cpp_arcade
** File description:
** Created by martin.januario@epitech.eu,
*/

#include <MapException.hpp>
#include "ManageMap.hpp"

ManageMap::ManageMap(int height, int width) : _map(width, height)
{
	if (height <= 25 || width <= 25)
		throw MapException("The minimum map size is (10, 10)",
			"Constructor");
	this->_posQixX = (std::size_t)width / 2 - 4;
	this->_posQixY = (std::size_t)height / 2 - 4;
	this->_qixPattern.insert({0, " *    * "
				     "  ****  "
				     " ****** "
				     "** ** **"
				     "********"
				     " **  ** "
				     "* *  * *"
				     "*      *"});
	this->_qixPattern.insert({1, "  *  *  "
				     " *    * "
				     "  *  *  "
				     " ****** "
				     "*  **  *"
				     "********"
				     " **  ** "
				     "* *  * *"});
	InitMap();
}
