/*
** EPITECH PROJECT, 2018
** cpp_arcade
** File description:
** Created by martin.januario@epitech.eu,
*/

#include "Game.hpp"

int ar::Qix::GoThroughTheMap(int x, int y)
{
	if (x < 0 || y < 0 || this->_manageMap._map.getHeight() <= y || this->_manageMap._map.getWidth() <= x)
		return 0;
	if (this->_manageMap._map[y][x] != MapPattern::WALKABLE &&
		this->_manageMap._map[y][x] != MapPattern::QIX) {
		if (this->_manageMap._map[y][x] == MapPattern::OLDBORDER)
			this->_manageMap._map[y][x] = MapPattern::BORDER;
		return 0;
	}
	if (x < this->_manageMap._map.getWidth() && y < this->_manageMap._map.getHeight() && x > 0 && y > 0) {
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

void ar::Qix::updateMap(void) {
	int **mapTmp = new int *[this->_manageMap._map.getHeight() + 1];
	for (int i = 0; i < this->_manageMap._map.getHeight(); ++i) {
		mapTmp[i] = new int[this->_manageMap._map.getWidth() + 1];
		for (int j = 0; j < this->_manageMap._map.getWidth(); ++j) {
			mapTmp[i][j] = this->_manageMap._map[i][j];
			if (this->_manageMap._map[i][j] == MapPattern::SHARKS)
				this->_manageMap._map[i][j] = MapPattern::BORDER;
			if (this->_manageMap._map[i][j] != MapPattern::BORDER && this->_manageMap._map[i][j] != MapPattern::OLDBORDER)
				this->_manageMap._map[i][j] = MapPattern::WALKABLE;
		}
		mapTmp[i][this->_manageMap._map.getWidth()] = 0;
	}
	mapTmp[this->_manageMap._map.getHeight()] = nullptr;

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
			if (mapTmp[idx_y][idx_x] == MapPattern::SHARKS || mapTmp[idx_y][idx_x] == MapPattern::TRAIL)
				this->_manageMap._map[idx_y][idx_x] = mapTmp[idx_y][idx_x];
		}
	}
	for (int i = 0; i < this->_manageMap._map.getHeight(); ++i) {
		delete[] mapTmp[i];
	}
	delete[] mapTmp;
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
