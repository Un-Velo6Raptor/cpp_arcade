/*
** EPITECH PROJECT, 2018
** cpp_arcade
** File description:
** Created by martin.januario@epitech.eu,
*/

#include "GameException.hpp"
#include "Game.hpp"

void ar::Qix::SetDirFlameToGo()
{
	if (this->_lastBorderPosY + 1 < this->_manageMap._map.getHeight() && this->_manageMap._map[this->_lastBorderPosY + 1][this->_lastBorderPosX] == TRAIL) {
		_flame->setPosY(this->_lastBorderPosY + 1);
		_flame->setPosX(this->_lastBorderPosX);
		_flame->setDir(DirObj::DOWN);
	} else if (this->_lastBorderPosY - 1 >= 0 && this->_manageMap._map[this->_lastBorderPosY - 1][this->_lastBorderPosX] == TRAIL) {
		_flame->setPosY(this->_lastBorderPosY - 1);
		_flame->setPosX(this->_lastBorderPosX);
		_flame->setDir(DirObj::UP);
	} else if (this->_lastBorderPosX + 1 < this->_manageMap._map.getWidth() && this->_manageMap._map[this->_lastBorderPosY][this->_lastBorderPosX + 1] == TRAIL) {
		_flame->setPosY(this->_lastBorderPosY);
		_flame->setPosX(this->_lastBorderPosX + 1);
		_flame->setDir(DirObj::RIGHT);
	} else if (this->_lastBorderPosX - 1 >= 0 && this->_manageMap._map[this->_lastBorderPosY][this->_lastBorderPosX - 1] == TRAIL) {
		_flame->setPosY(this->_lastBorderPosY);
		_flame->setPosX(this->_lastBorderPosX - 1);
		_flame->setDir(DirObj::LEFT);
	}
}

void ar::Qix::KeyUpPressed(void)
{
	bool last = this->_isPlayerStopped;

	this->_isPlayerStopped = (this->_actualDir == DirObj::DOWN);
	if (!last && this->_isPlayerStopped && !this->_flame) {
		_flame = new ManageSharks(this->_manageMap, true);
		SetDirFlameToGo();
		_flame->setLastChar(MapPattern::TRAIL);
		this->_manageMap._map[this->_manageMap._map.getHeight() - 1][this->_manageMap._map.getWidth() - 1] = MapPattern::BORDER;
		this->_manageMap._map[_flame->getPosY()][_flame->getPosX()] = MapPattern::SHARKS;

	}

	if (!this->_isPlayerStopped)
		this->_actualDir = DirObj::UP;
}

void ar::Qix::KeyDownPressed(void)
{
	bool last = this->_isPlayerStopped;

	this->_isPlayerStopped = (this->_actualDir == DirObj::UP);
	if (!last && this->_isPlayerStopped && !this->_flame) {
		_flame = new ManageSharks(this->_manageMap, true);
		SetDirFlameToGo();
		_flame->setLastChar(MapPattern::TRAIL);
		this->_manageMap._map[this->_manageMap._map.getHeight() - 1][this->_manageMap._map.getWidth() - 1] = MapPattern::BORDER;
		this->_manageMap._map[_flame->getPosY()][_flame->getPosX()] = MapPattern::SHARKS;

	}

	if (!this->_isPlayerStopped)
		this->_actualDir = DirObj::DOWN;
}

void ar::Qix::KeyLeftPressed(void)
{
	bool last = this->_isPlayerStopped;

	this->_isPlayerStopped = (this->_actualDir == DirObj::RIGHT);
	if (!last && this->_isPlayerStopped && !this->_flame) {
		_flame = new ManageSharks(this->_manageMap, true);
		SetDirFlameToGo();
		_flame->setLastChar(MapPattern::TRAIL);
		this->_manageMap._map[this->_manageMap._map.getHeight() - 1][this->_manageMap._map.getWidth() - 1] = MapPattern::BORDER;
		this->_manageMap._map[_flame->getPosY()][_flame->getPosX()] = MapPattern::SHARKS;

	}

	if (!this->_isPlayerStopped)
		this->_actualDir = DirObj::LEFT;
}

void ar::Qix::KeyRightPressed(void)
{
	bool last = this->_isPlayerStopped;

	this->_isPlayerStopped = (this->_actualDir == DirObj::LEFT);
	if (!last && this->_isPlayerStopped && !this->_flame) {
		_flame = new ManageSharks(this->_manageMap, true);
		SetDirFlameToGo();
		_flame->setLastChar(MapPattern::TRAIL);
		this->_manageMap._map[this->_manageMap._map.getHeight() - 1][this->_manageMap._map.getWidth() - 1] = MapPattern::BORDER;
		this->_manageMap._map[_flame->getPosY()][_flame->getPosX()] = MapPattern::SHARKS;

	}

	if (!this->_isPlayerStopped)
		this->_actualDir = DirObj::RIGHT;
}

void ar::Qix::manageKey(const ar::Event &key)
{
	static void (ar::Qix::*keyPressed[4])(void) = {&ar::Qix::KeyUpPressed,
		&ar::Qix::KeyDownPressed, &ar::Qix::KeyLeftPressed,
		&ar::Qix::KeyRightPressed};

	if (this->_manageMap._map[this->_manageMap._map.getPlayerY()][this->_manageMap._map.getPlayerX()] == MapPattern::PLAYER)
		this->_manageMap._map[this->_manageMap._map.getPlayerY()][this->_manageMap._map.getPlayerX()] = this->_behindPlayer;

	if (key == Event::AR_PAUSE)
		this->_isPaused = !this->_isPaused;
	else if (this->_isPaused)
		return;
	else if ((int)key < 4)
		(this->*keyPressed[key])();
}