/*
** EPITECH PROJECT, 2018
** cpp_arcade
** File description:
** Created by martin.januario@epitech.eu,
*/

#include "Sharks.hpp"

ar::ManageSharks::ManageSharks(ar::ManageMap &manageMap, bool randOk)
{
	initSharksOnTheMap(manageMap, randOk);
}

ar::ManageSharks::~ManageSharks()
{
}

void ar::ManageSharks::getAllDirSharksVerticaly(ar::ManageMap &manageMap,
	std::vector<ar::DirObj> &result
)
{
	if (this->_dir != ar::DirObj::DOWN && this->_posY > 0 &&
		(manageMap._map[this->_posY - 1][this->_posX] == ar::MapPattern::BORDER ||
			manageMap._map[this->_posY - 1][this->_posX] == ar::MapPattern::SHARKS ||
			manageMap._map[this->_posY - 1][this->_posX] == ar::MapPattern::TRAIL ||
			((manageMap._map[this->_posY - 1][this->_posX] == ar::MapPattern::OLDBORDER) &&
				(manageMap._map[this->_posY][this->_posX] == ar::MapPattern::OLDBORDER ||
					manageMap._map[this->_posY][this->_posX] == ar::MapPattern::SHARKS))))
		result.push_back(DirObj::UP);
	if (this->_dir != ar::DirObj::UP && this->_posY < (std::size_t)manageMap._map.getHeight() - 1 &&
		(manageMap._map[this->_posY + 1][this->_posX] == ar::MapPattern::BORDER ||
			manageMap._map[this->_posY + 1][this->_posX] == ar::MapPattern::SHARKS ||
			manageMap._map[this->_posY + 1][this->_posX] == ar::MapPattern::TRAIL ||
			(manageMap._map[this->_posY + 1][this->_posX] == ar::MapPattern::OLDBORDER &&
				(manageMap._map[this->_posY][this->_posX] == ar::MapPattern::OLDBORDER ||
					manageMap._map[this->_posY][this->_posX] == ar::MapPattern::SHARKS))))
		result.push_back(ar::DirObj::DOWN);
}

std::vector<ar::DirObj> ar::ManageSharks::getAllDirSharks(ar::ManageMap &manageMap)
{
	std::vector<ar::DirObj> result;

	if (this->_dir != ar::DirObj::RIGHT && this->_posX > 0 &&
		(manageMap._map[this->_posY][this->_posX - 1] == ar::MapPattern::BORDER ||
			manageMap._map[this->_posY][this->_posX - 1] == ar::MapPattern::SHARKS ||
			manageMap._map[this->_posY][this->_posX - 1] == ar::MapPattern::TRAIL ||
			(manageMap._map[this->_posY][this->_posX - 1] == ar::MapPattern::OLDBORDER &&
				(manageMap._map[this->_posY][this->_posX] == ar::MapPattern::OLDBORDER ||
					manageMap._map[this->_posY][this->_posX] == ar::MapPattern::SHARKS))))
		result.push_back(DirObj::LEFT);
	if (this->_dir != ar::DirObj::LEFT && this->_posX < (std::size_t)manageMap._map.getWidth() - 1 &&
		(manageMap._map[this->_posY][this->_posX + 1] == ar::MapPattern::BORDER ||
			manageMap._map[this->_posY][this->_posX + 1] == ar::MapPattern::SHARKS ||
			manageMap._map[this->_posY][this->_posX + 1] == ar::MapPattern::TRAIL ||
			(manageMap._map[this->_posY][this->_posX + 1] == ar::MapPattern::OLDBORDER &&
				(manageMap._map[this->_posY][this->_posX] == ar::MapPattern::OLDBORDER ||
					manageMap._map[this->_posY][this->_posX] == ar::MapPattern::SHARKS))))
		result.push_back(DirObj::RIGHT);
	getAllDirSharksVerticaly(manageMap, result);
	return result;
}

ar::DirObj ar::ManageSharks::findTheDirToGoWithTrail(ar::ManageMap &manageMap, std::vector<ar::DirObj> &dirAccess)
{
	ar::DirObj result = ar::DirObj::UNKNOWN;
	std::vector<ar::DirObj> tmpAccess;

	for (auto it = dirAccess.begin(); it != dirAccess.end() ;) {
		if (*it == ar::DirObj::DOWN && (manageMap._map[this->_posY + 1][this->_posX] == ar::MapPattern::BORDER || manageMap._map[this->_posY + 1][this->_posX] == ar::MapPattern::TRAIL)) {
			tmpAccess.push_back(*it);
			dirAccess.erase(it);
		} else if (*it == ar::DirObj::UP && (manageMap._map[this->_posY - 1][this->_posX] == ar::MapPattern::BORDER || manageMap._map[this->_posY - 1][this->_posX] == ar::MapPattern::TRAIL)) {
			tmpAccess.push_back(*it);
			dirAccess.erase(it);
		} else if (*it == ar::DirObj::LEFT && (manageMap._map[this->_posY][this->_posX - 1] == ar::MapPattern::BORDER || manageMap._map[this->_posY][this->_posX - 1] == ar::MapPattern::TRAIL)) {
			tmpAccess.push_back(*it);
			dirAccess.erase(it);
		} else if (*it == ar::DirObj::RIGHT && (manageMap._map[this->_posY][this->_posX + 1] == ar::MapPattern::BORDER || manageMap._map[this->_posY][this->_posX + 1] == ar::MapPattern::TRAIL)) {
			tmpAccess.push_back(*it);
			dirAccess.erase(it);
		} else
			++it;
	}
	if (tmpAccess.empty() && dirAccess.empty())
		return result;
	result = (!tmpAccess.empty()) ? tmpAccess[rand() % tmpAccess.size()] : dirAccess[rand() % dirAccess.size()];
	return result;
}

ar::DirObj ar::ManageSharks::findTheDirToGo(ar::ManageMap &manageMap)
{
	std::vector<ar::DirObj> dirAccess;

	if (manageMap._map[this->_posY][this->_posX] != ar::MapPattern::BORDER &&
		manageMap._map[this->_posY][this->_posX] != ar::MapPattern::OLDBORDER &&
		manageMap._map[this->_posY][this->_posX] != ar::MapPattern::SHARKS) {
		manageMap._map[manageMap._map.getHeight() - 1][manageMap._map.getWidth() - 1] = ar::MapPattern::SHARKS;
		this->_posY = (std::size_t)manageMap._map.getHeight() - 1;
		this->_posX = (std::size_t)manageMap._map.getWidth() - 1;
	} else {
		dirAccess = getAllDirSharks(manageMap);
	}
	return findTheDirToGoWithTrail(manageMap, dirAccess);
}

void ar::ManageSharks::initSharksOnTheMap(ar::ManageMap &manageMap, bool dir)
{
	this->_dir = !dir ? ar::DirObj::LEFT : ar::DirObj::UP;

	this->_posY = (std::size_t)manageMap._map.getHeight() - 1;
	this->_posX = (std::size_t)manageMap._map.getWidth() - 1;
	manageMap._map[this->_posY][this->_posX] = ar::MapPattern::SHARKS;
	_lastChar = ar::MapPattern::BORDER;
}

int ar::ManageSharks::sharksEatPlayer(ManageMap &manageMap)
{
	int ret = 0;

	if ((std::size_t)manageMap._map.getPlayerX() == this->_posX && (std::size_t)manageMap._map.getPlayerY() == this->_posY)
		ret = 1;
	return ret;
}

void ar::ManageSharks::setDir(DirObj dir)
{
	this->_dir = dir;
}

void ar::ManageSharks::setPosX(std::size_t x)
{
	this->_posX = x;
}

void ar::ManageSharks::setPosY(std::size_t y)
{
	this->_posY = y;
}

void ar::ManageSharks::setLastChar(MapPattern pattern)
{
	this->_lastChar = pattern;
}

std::size_t ar::ManageSharks::getPosY() const
{
	return this->_posY;
}

std::size_t ar::ManageSharks::getPosX() const
{
	return this->_posX;
}

ar::MapPattern ar::ManageSharks::getLastChar() const
{
	return this->_lastChar;
}

int ar::ManageSharks::GetCharTo(ar::ManageMap &manageMap, int x, int y)
{
	int result = -1;

	if (x < 0 || y < 0 || x >= manageMap._map.getWidth() || y >= manageMap._map.getHeight())
		return result;
	result = manageMap._map[y][x];
	return result;
}

bool ar::ManageSharks::isAnotherTrailAround(ar::ManageMap &manageMap)
{
	if (GetCharTo(manageMap, this->_posX, this->_posY + 1) == ar::MapPattern::TRAIL || GetCharTo(manageMap, this->_posX, this->_posY - 1) == ar::MapPattern::TRAIL ||
		GetCharTo(manageMap, this->_posX + 1, this->_posY) == ar::MapPattern::TRAIL || GetCharTo(manageMap, this->_posX - 1, this->_posY) == ar::MapPattern::TRAIL)
		return true;
	return false;
}

void ar::ManageSharks::checkDirToGo(ManageMap &manageMap, int x, int y)
{
	if (_lastChar == ar::MapPattern::TRAIL && !isAnotherTrailAround(manageMap))
		_lastChar = (manageMap._map[this->_posY][this->_posX] == ar::WALKABLE) ? ar::WALKABLE : ar::BORDER;
	manageMap._map[this->_posY][this->_posX] = _lastChar;
	this->_posX += x;
	this->_posY += y;
}

int ar::ManageSharks::loopSharks(ar::ManageMap &manageMap)
{
	ar::DirObj tmp = findTheDirToGo(manageMap);

	switch (tmp) {
	case ar::DirObj::RIGHT:
		checkDirToGo(manageMap, 1, 0);
		break;
	case ar::DirObj::LEFT:
		checkDirToGo(manageMap, -1, 0);
		break;
	case ar::DirObj::UP:
		checkDirToGo(manageMap, 0, -1);
		break;
	case ar::DirObj::DOWN:
		checkDirToGo(manageMap, 0, 1);
		break;
	default:
		manageMap._map[this->_posY][this->_posX] = ar::MapPattern::WALKABLE;
		initSharksOnTheMap(manageMap, true);
		return sharksEatPlayer(manageMap);
	}
	this->_dir = tmp;
	_lastChar = (ar::MapPattern)manageMap._map[this->_posY][this->_posX];
	if (_lastChar == ar::MapPattern::SHARKS)
		_lastChar = ar::MapPattern::BORDER;
	manageMap._map[this->_posY][this->_posX] = ar::MapPattern::SHARKS;
	return sharksEatPlayer(manageMap);
}