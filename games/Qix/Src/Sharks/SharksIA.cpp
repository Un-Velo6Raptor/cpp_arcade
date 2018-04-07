/*
** EPITECH PROJECT, 2018
** cpp_arcade
** File description:
** Created by martin.januario@epitech.eu,
*/

#include "Sharks.hpp"

std::vector<DirObj> ManageSharks::getAllDirSharks(ManageMap &manageMap)
{
	std::vector<DirObj> result;

	if (this->_dir != DirObj::RIGHT && this->_posX > 0 &&
		(manageMap._map[this->_posY][this->_posX - 1] == MapPattern::BORDER ||
			manageMap._map[this->_posY][this->_posX - 1] == MapPattern::SHARKS ||
			manageMap._map[this->_posY][this->_posX - 1] == MapPattern::TRAIL ||
			(manageMap._map[this->_posY][this->_posX - 1] == MapPattern::OLDBORDER &&
				(manageMap._map[this->_posY][this->_posX] == MapPattern::OLDBORDER || manageMap._map[this->_posY][this->_posX] == MapPattern::SHARKS))))
		result.push_back(DirObj::LEFT);
	if (this->_dir != DirObj::LEFT && this->_posX < (std::size_t)manageMap._map.getWidth() - 1 &&
		(manageMap._map[this->_posY][this->_posX + 1] == MapPattern::BORDER ||
			manageMap._map[this->_posY][this->_posX + 1] == MapPattern::SHARKS ||
			manageMap._map[this->_posY][this->_posX + 1] == MapPattern::TRAIL ||
			(manageMap._map[this->_posY][this->_posX + 1] == MapPattern::OLDBORDER &&
				(manageMap._map[this->_posY][this->_posX] == MapPattern::OLDBORDER || manageMap._map[this->_posY][this->_posX] == MapPattern::SHARKS))))
		result.push_back(DirObj::RIGHT);
	if (this->_dir != DirObj::DOWN && this->_posY > 0 &&
		(manageMap._map[this->_posY - 1][this->_posX] == MapPattern::BORDER ||
			manageMap._map[this->_posY - 1][this->_posX] == MapPattern::SHARKS ||
			manageMap._map[this->_posY - 1][this->_posX] == MapPattern::TRAIL ||
			((manageMap._map[this->_posY - 1][this->_posX] == MapPattern::OLDBORDER) &&
				(manageMap._map[this->_posY][this->_posX] == MapPattern::OLDBORDER || manageMap._map[this->_posY][this->_posX] == MapPattern::SHARKS))))
		result.push_back(DirObj::UP);
	if (this->_dir != DirObj::UP && this->_posY < (std::size_t)manageMap._map.getHeight() - 1 &&
		(manageMap._map[this->_posY + 1][this->_posX] == MapPattern::BORDER ||
			manageMap._map[this->_posY + 1][this->_posX] == MapPattern::SHARKS ||
			manageMap._map[this->_posY + 1][this->_posX] == MapPattern::TRAIL ||
			(manageMap._map[this->_posY + 1][this->_posX] == MapPattern::OLDBORDER &&
				(manageMap._map[this->_posY][this->_posX] == MapPattern::OLDBORDER || manageMap._map[this->_posY][this->_posX] == MapPattern::SHARKS))))
		result.push_back(DirObj::DOWN);
	return result;
}

DirObj ManageSharks::findTheDirToGo(ManageMap &manageMap)
{
	DirObj result = DirObj::UNKNOWN;
	std::vector<DirObj> dirAccess;

	if (manageMap._map[this->_posY][this->_posX] != MapPattern::BORDER &&
		manageMap._map[this->_posY][this->_posX] != MapPattern::OLDBORDER &&
		manageMap._map[this->_posY][this->_posX] != MapPattern::SHARKS) {
		manageMap._map[manageMap._map.getHeight() - 1][manageMap._map.getWidth() - 1] = MapPattern::SHARKS;
		this->_posY = (std::size_t)manageMap._map.getHeight() - 1;
		this->_posX = (std::size_t)manageMap._map.getWidth() - 1;
	} else {
		dirAccess = getAllDirSharks(manageMap);
	}
	if (!dirAccess.empty()) {
		std::vector<DirObj> tmpAccess;
		for (auto it = dirAccess.begin(); it != dirAccess.end() ;) {
			if (*it == DirObj::DOWN && (manageMap._map[this->_posY + 1][this->_posX] == MapPattern::BORDER || manageMap._map[this->_posY + 1][this->_posX] == MapPattern::TRAIL)) {
				tmpAccess.push_back(*it);
				dirAccess.erase(it);
			}
			else if (*it == DirObj::UP && (manageMap._map[this->_posY - 1][this->_posX] == MapPattern::BORDER || manageMap._map[this->_posY - 1][this->_posX] == MapPattern::TRAIL)) {
				tmpAccess.push_back(*it);
				dirAccess.erase(it);
			}
			else if (*it == DirObj::LEFT && (manageMap._map[this->_posY][this->_posX - 1] == MapPattern::BORDER || manageMap._map[this->_posY][this->_posX - 1] == MapPattern::TRAIL)) {
				tmpAccess.push_back(*it);
				dirAccess.erase(it);
			}
			else if (*it == DirObj::RIGHT && (manageMap._map[this->_posY][this->_posX + 1] == MapPattern::BORDER || manageMap._map[this->_posY][this->_posX + 1] == MapPattern::TRAIL)) {
				tmpAccess.push_back(*it);
				dirAccess.erase(it);
			} else
				++it;
		}
		if (!tmpAccess.empty())
			result = tmpAccess[rand() % tmpAccess.size()];
		else
			result = dirAccess[rand() % dirAccess.size()];
	}

	return result;
}