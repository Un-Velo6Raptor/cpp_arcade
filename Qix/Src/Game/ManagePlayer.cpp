/*
** EPITECH PROJECT, 2018
** cpp_arcade
** File description:
** Created by martin.januario@epitech.eu,
*/

#include "Game.hpp"

int ar::Qix::GetCharTo(int x, int y)
{
	int result = -1;

	if (x < 0 || y < 0 || x >= this->_manageMap._map.getWidth() || y >= this->_manageMap._map.getHeight())
		return result;
	result = this->_manageMap._map[y][x];
	return result;
}

int ar::Qix::ToUp(int charFrom)
{
	int charTo = GetCharTo(this->_manageMap._map.getPlayerX(), this->_manageMap._map.getPlayerY() - 1);

	if (charTo == MapPattern::QIX)
		return 1;
	if (charTo == -1 || (charTo != MapPattern::WALKABLE && charTo != MapPattern::BORDER))
		return 0;
	if (charTo == MapPattern::WALKABLE) {
		charTo = GetCharTo(this->_manageMap._map.getPlayerX(), this->_manageMap._map.getPlayerY() - 2);
		if (charTo == MapPattern::TRAIL || charTo == MapPattern::SHARKS)
			return 0;
		this->_manageMap._map[this->_manageMap._map.getPlayerY() - 1][this->_manageMap._map.getPlayerX()] = MapPattern::TRAIL;
		if (charFrom == MapPattern::BORDER) {
			this->_lastBorderPosX = this->_manageMap._map.getPlayerX();
			this->_lastBorderPosY= this->_manageMap._map.getPlayerY();
		}
	} else if (charTo == MapPattern::BORDER && charFrom == MapPattern::TRAIL) {
		fillBox();
	}
	this->_manageMap._map.setPlayerY(this->_manageMap._map.getPlayerY() - 1);
	return 0;
}

int ar::Qix::ToDown(int charFrom)
{
	int charTo = GetCharTo(this->_manageMap._map.getPlayerX(), this->_manageMap._map.getPlayerY() + 1);

	if (charTo == MapPattern::QIX)
		return 1;
	if (charTo == -1 || (charTo != MapPattern::WALKABLE && charTo != MapPattern::BORDER))
		return 0;
	if (charTo == MapPattern::WALKABLE) {
		charTo = GetCharTo(this->_manageMap._map.getPlayerX(), this->_manageMap._map.getPlayerY() + 2);
		if (charTo == MapPattern::TRAIL || charTo == MapPattern::SHARKS)
			return 0;
		this->_manageMap._map[this->_manageMap._map.getPlayerY() + 1][this->_manageMap._map.getPlayerX()] = MapPattern::TRAIL;
		if (charFrom == MapPattern::BORDER) {
			this->_lastBorderPosX = this->_manageMap._map.getPlayerX();
			this->_lastBorderPosY= this->_manageMap._map.getPlayerY();
		}
	} else if (charTo == MapPattern::BORDER && charFrom == MapPattern::TRAIL) {
		fillBox();
	}
	this->_manageMap._map.setPlayerY(this->_manageMap._map.getPlayerY() + 1);
	return 0;
}

int ar::Qix::ToLeft(int charFrom)
{
	int charTo = GetCharTo(this->_manageMap._map.getPlayerX() - 1, this->_manageMap._map.getPlayerY());

	if (charTo == MapPattern::QIX)
		return 1;
	if (charTo == -1 || (charTo != MapPattern::WALKABLE && charTo != MapPattern::BORDER))
		return 0;
	if (charTo == MapPattern::WALKABLE) {
		charTo = GetCharTo(this->_manageMap._map.getPlayerX() - 2, this->_manageMap._map.getPlayerY());
		if (charTo == MapPattern::TRAIL || charTo == MapPattern::SHARKS)
			return 0;
		this->_manageMap._map[this->_manageMap._map.getPlayerY()][this->_manageMap._map.getPlayerX() - 1] = MapPattern::TRAIL;
		if (charFrom == MapPattern::BORDER) {
			this->_lastBorderPosX = this->_manageMap._map.getPlayerX();
			this->_lastBorderPosY= this->_manageMap._map.getPlayerY();
		}
	} else if (charTo == MapPattern::BORDER && charFrom == MapPattern::TRAIL) {
		fillBox();
	}
	this->_manageMap._map.setPlayerX(this->_manageMap._map.getPlayerX() - 1);
	return 0;
}

int ar::Qix::ToRight(int charFrom)
{
	int charTo = GetCharTo(this->_manageMap._map.getPlayerX() + 1, this->_manageMap._map.getPlayerY());

	if (charTo == MapPattern::QIX)
		return 1;
	if (charTo == -1 || (charTo != MapPattern::WALKABLE && charTo != MapPattern::BORDER))
		return 0;
	if (charTo == MapPattern::WALKABLE) {
		charTo = GetCharTo(this->_manageMap._map.getPlayerX() + 2, this->_manageMap._map.getPlayerY());
		if (charTo == MapPattern::TRAIL || charTo == MapPattern::SHARKS)
			return 0;
		this->_manageMap._map[this->_manageMap._map.getPlayerY()][this->_manageMap._map.getPlayerX() + 1] = MapPattern::TRAIL;
		if (charFrom == MapPattern::BORDER) {
			this->_lastBorderPosX = this->_manageMap._map.getPlayerX();
			this->_lastBorderPosY= this->_manageMap._map.getPlayerY();
		}
	} else if (charTo == MapPattern::BORDER && charFrom == MapPattern::TRAIL) {
		fillBox();
	}
	this->_manageMap._map.setPlayerX(this->_manageMap._map.getPlayerX() + 1);
	return 0;
}

int ar::Qix::moovePlayer(void)
{
	static int (ar::Qix::*MoveTo[4])(int) = {&ar::Qix::ToLeft,
		&ar::Qix::ToRight, &ar::Qix::ToDown, &ar::Qix::ToUp};
	int charFrom = this->_manageMap._map[this->_manageMap._map.getPlayerY()][this->_manageMap._map.getPlayerX()];
	int ret = 0;

	if (!this->_isPlayerStopped)
		ret = (this->*MoveTo[this->_actualDir])(charFrom);
	if (ret) {
		this->_life -= 1;
		resetSpecificCharMap(MapPattern::TRAIL);
		this->_isPlayerStopped = true;
		this->_manageMap._map.setPlayerY(this->_lastBorderPosY);
		this->_manageMap._map.setPlayerX(this->_lastBorderPosX);
	}
	return ret;
}