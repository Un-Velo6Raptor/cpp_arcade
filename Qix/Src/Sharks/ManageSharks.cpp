/*
** EPITECH PROJECT, 2018
** cpp_arcade
** File description:
** Created by martin.januario@epitech.eu,
*/

#include "Sharks.hpp"

void ManageSharks::initSharksOnTheMap(ManageMap &manageMap)
{
	this->_dir = !(rand() % 2) ? DirObj::LEFT : DirObj::UP;
	
	this->_posY = manageMap._map.getHeight() - 1;
	this->_posX = manageMap._map.getWidth() - 1;
	manageMap._map[this->_posY][this->_posX] = MapPattern::SHARKS;
}

int ManageSharks::loopSharks(ManageMap &manageMap, std::size_t lastBorderPosX, std::size_t lastBorderPosY)
{
	DirObj dirToGo = findTheDirToGo(manageMap, lastBorderPosX, lastBorderPosY);
	int result = 0;

	std::cout << "I go to: " << dirToGo << std::endl;
	return result;
}