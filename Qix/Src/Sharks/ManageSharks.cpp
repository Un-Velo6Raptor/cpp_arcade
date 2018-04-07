/*
** EPITECH PROJECT, 2018
** cpp_arcade
** File description:
** Created by martin.januario@epitech.eu,
*/

#include "Sharks.hpp"

void ManageSharks::initSharksOnTheMap(ManageMap &manageMap, bool dir)
{
	this->_dir = !dir ? DirObj::LEFT : DirObj::UP;

	this->_posY = (std::size_t)manageMap._map.getHeight() - 1;
	this->_posX = (std::size_t)manageMap._map.getWidth() - 1;
	manageMap._map[this->_posY][this->_posX] = MapPattern::SHARKS;
	_lastChar = MapPattern::BORDER;
}

int ManageSharks::sharksEatPlayer(ManageMap &manageMap)
{
	int ret = 0;

	if ((std::size_t)manageMap._map.getPlayerX() == this->_posX && (std::size_t)manageMap._map.getPlayerY() == this->_posY)
		ret = 1;
	return ret;
}

void ManageSharks::setDir(DirObj dir)
{
	this->_dir = dir;
}

void ManageSharks::setPosX(std::size_t x)
{
	this->_posX = x;
}

void ManageSharks::setPosY(std::size_t y)
{
	this->_posY = y;
}

void ManageSharks::setLastChar(MapPattern pattern)
{
	this->_lastChar = pattern;
}

std::size_t ManageSharks::getPosY() const
{
	return this->_posY;
}

std::size_t ManageSharks::getPosX() const
{
	return this->_posX;
}

MapPattern ManageSharks::getLastChar() const
{
	return this->_lastChar;
}

int ManageSharks::loopSharks(ManageMap &manageMap)
{
	DirObj tmp = findTheDirToGo(manageMap);

	switch (tmp) {
	case DirObj::RIGHT:
		if (_lastChar == MapPattern::TRAIL && manageMap._map[this->_posY][this->_posX + 1] != MapPattern::TRAIL)
			_lastChar = (manageMap._map[this->_posY][this->_posX] == WALKABLE) ? WALKABLE : BORDER;
		manageMap._map[this->_posY][this->_posX] = _lastChar;
		this->_posX++;
		break;
	case DirObj::LEFT:
		if (_lastChar == MapPattern::TRAIL && manageMap._map[this->_posY][this->_posX - 1] != MapPattern::TRAIL)
			_lastChar = (manageMap._map[this->_posY][this->_posX] == WALKABLE) ? WALKABLE : BORDER;
		manageMap._map[this->_posY][this->_posX] = _lastChar;
		this->_posX--;
		break;
	case DirObj::UP:
		if (_lastChar == MapPattern::TRAIL && manageMap._map[this->_posY - 1][this->_posX] != MapPattern::TRAIL)
			_lastChar = (manageMap._map[this->_posY][this->_posX] == WALKABLE) ? WALKABLE : BORDER;
		manageMap._map[this->_posY][this->_posX] = _lastChar;
		this->_posY--;
		break;
	case DirObj::DOWN:
		if (_lastChar == MapPattern::TRAIL && manageMap._map[this->_posY + 1][this->_posX] != MapPattern::TRAIL)
			_lastChar = (manageMap._map[this->_posY][this->_posX] == WALKABLE) ? WALKABLE : BORDER;
		manageMap._map[this->_posY][this->_posX] = _lastChar;
		this->_posY++;
		break;
	default:
		manageMap._map[this->_posY][this->_posX] = MapPattern::WALKABLE;
		initSharksOnTheMap(manageMap, true);
		return sharksEatPlayer(manageMap);
	}
	this->_dir = tmp;
	_lastChar = (MapPattern)manageMap._map[this->_posY][this->_posX];
	if (_lastChar == MapPattern::SHARKS)
		_lastChar = MapPattern::BORDER;
	manageMap._map[this->_posY][this->_posX] = MapPattern::SHARKS;
	return sharksEatPlayer(manageMap);
}