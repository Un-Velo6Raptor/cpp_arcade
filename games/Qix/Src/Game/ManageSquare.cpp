/*
** EPITECH PROJECT, 2018
** cpp_arcade
** File description:
** Created by martin.januario@epitech.eu,
*/

#include "Game.hpp"

int ar::Qix::GoThroughTheMap(int x, int y)
{
	if (this->_manageMap._map[y][x] != MapPattern::WALKABLE &&
		this->_manageMap._map[y][x] != MapPattern::QIX) {
		if (this->_manageMap._map[y][x] == MapPattern::OLDBORDER)
			this->_manageMap._map[y][x] = MapPattern::BORDER;
		return 0;
	}

	if (x < this->_manageMap._map.getWidth() || y < this->_manageMap._map.getHeight() || x > 0 || y > 0) {
		this->_manageMap._map[y][x] = MapPattern::FILLQIXTMP;

		GoThroughTheMap(x, y + 1);
		GoThroughTheMap(x, y - 1);

		GoThroughTheMap(x + 1, y);
		GoThroughTheMap(x - 1, y);

		GoThroughTheMap(x + 1, y + 1);
		GoThroughTheMap(x - 1, y - 1);

		GoThroughTheMap(x - 1, y + 1);
		GoThroughTheMap(x + 1, y - 1);
	}

	return 0;
}

void ar::Qix::fillBox(bool opt)
{
	for (int idx_y = 0;
		idx_y < this->_manageMap._map.getHeight(); ++idx_y) {
		for (int idx_x = 0;
			idx_x < this->_manageMap._map.getWidth(); ++idx_x) {
			if (this->_manageMap._map[idx_y][idx_x] == MapPattern::BORDER || (this->_manageMap._map[idx_y][idx_x] == MapPattern::TRAIL && !opt))
				this->_manageMap._map[idx_y][idx_x] = MapPattern::OLDBORDER;
		}
	}

	GoThroughTheMap((int)this->_manageMap._posQixX,
		(int)this->_manageMap._posQixY);

	for (int idx_y = 0;
		idx_y < this->_manageMap._map.getHeight(); ++idx_y) {
		for (int idx_x = 0;
			idx_x < this->_manageMap._map.getWidth(); ++idx_x) {
			if (this->_manageMap._map[idx_y][idx_x] == MapPattern::WALKABLE)
				this->_manageMap._map[idx_y][idx_x] = MapPattern::NOWALKABLE;
			else if (this->_manageMap._map[idx_y][idx_x] == MapPattern::FILLQIXTMP)
			this->_manageMap._map[idx_y][idx_x] = MapPattern::WALKABLE;
		}
	}
	this->_manageMap.PlaceQixOntTheMap(0);
}

void ar::Qix::resetSpecificCharMap(MapPattern car)
{
	for (int idx_y = 0;
		idx_y < this->_manageMap._map.getHeight(); ++idx_y) {
		for (int idx_x = 0;
			idx_x < this->_manageMap._map.getWidth(); ++idx_x) {
			if (this->_manageMap._map[idx_y][idx_x] == car)
				this->_manageMap._map[idx_y][idx_x] = MapPattern::WALKABLE;
		}
	}
}