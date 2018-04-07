/*
** EPITECH PROJECT, 2018
** cpp_arcade
** File description:
** Created by martin.januario@epitech.eu,
*/

#include "Game.hpp"
#include "../../Include/Enum.hpp"

// Todo: Ajouter le timer
void ar::Qix::loop() // Todo: A faire
{
	static int lastPosX = 0;
	static int lastPosY = 0;

	if (clock() - _time < 100000 || _isPaused == true)
		return;
	if (this->_manageMap._map[this->_manageMap._map.getPlayerY()][this->_manageMap._map.getPlayerX()] == MapPattern::PLAYER)
		this->_manageMap._map[this->_manageMap._map.getPlayerY()][this->_manageMap._map.getPlayerX()] = this->_behindPlayer;

	moovePlayer();

	if (_flame && this->_manageMap._map[this->_manageMap._map.getPlayerY()][this->_manageMap._map.getPlayerX()] != MapPattern::TRAIL) {
		this->_manageMap._map[_flame->getPosY()][_flame->getPosX()] = _flame->getLastChar();
		delete _flame;
		_flame = nullptr;
	}

	for (auto it = this->_listSharks.begin();
		it != this->_listSharks.end(); ++it) {
		if ((*it).loopSharks(this->_manageMap) == 1) {
			this->_life--;
			if (this->_manageMap._map[this->_manageMap._map.getPlayerY()][this->_manageMap._map.getPlayerX()] !=
				MapPattern::BORDER && this->_manageMap._map[this->_manageMap._map.getPlayerY()][this->_manageMap._map.getPlayerX()] !=
				MapPattern::SHARKS) {
				this->_manageMap._map.setPlayerY(
					this->_lastBorderPosY);
				this->_manageMap._map.setPlayerX(
					this->_lastBorderPosX);
			}
			resetSpecificCharMap(MapPattern::TRAIL);
		}
	}
	if (_flame && _flame->loopSharks(this->_manageMap) == 1) {
		this->_life--;
		this->_manageMap._map.setPlayerY(this->_lastBorderPosY);
		this->_manageMap._map.setPlayerX(this->_lastBorderPosX);
		this->_manageMap._map[_flame->getPosY()][_flame->getPosX()] = WALKABLE;
		resetSpecificCharMap(MapPattern::TRAIL);
		delete _flame;
		_flame = nullptr;
	}
	fillBox(true);
	randomMoveQix();

	if (lastPosX == this->_manageMap._map.getPlayerX() && lastPosY == this->_manageMap._map.getPlayerY() && !this->_flame && this->_manageMap._map[this->_manageMap._map.getPlayerY()][this->_manageMap._map.getPlayerX()] == MapPattern::TRAIL) {
		_flame = new ManageSharks(this->_manageMap, true);
		SetDirFlameToGo();
		_flame->setLastChar(MapPattern::TRAIL);
		this->_manageMap._map[this->_manageMap._map.getHeight() - 1][this->_manageMap._map.getWidth() - 1] = MapPattern::BORDER;
		this->_manageMap._map[_flame->getPosY()][_flame->getPosX()] = MapPattern::SHARKS;
	}

	lastPosX = this->_manageMap._map.getPlayerX();
	lastPosY = this->_manageMap._map.getPlayerY();
	_time = clock();
	updateScore();
}

void ar::Qix::setPause()
{
	this->_isPaused = true;
}

void ar::Qix::updateScore() {
	int sizeMob = 64;
	int walkableArea = 0;

	for (int y = 0; y < this->_manageMap._map.getHeight(); ++y) {
		for (int x = 0; x < this->_manageMap._map.getWidth(); ++x) {
			if (this->_manageMap._map[y][x] ==
				MapPattern::WALKABLE ||
				this->_manageMap._map[y][x] ==
					MapPattern::TRAIL)
				walkableArea++;
		}
	}
	float percent = (int)(((float)walkableArea /
		(float)((this->_manageMap._map.getHeight() - 1) *
			(this->_manageMap._map.getWidth() - 1) - sizeMob)) *
		100);
	this->_data.score = int((100 - percent) * 100);
}

bool ar::Qix::isGameOver()
{
	int sizeMob = 64;
	int walkableArea = 0;

	if (this->_manageMap._map[this->_manageMap._map.getPlayerY()][this->_manageMap._map.getPlayerX()] == MapPattern::PLAYER)
		this->_manageMap._map[this->_manageMap._map.getPlayerY()][this->_manageMap._map.getPlayerX()] = this->_behindPlayer;
	if (_life <= 0)
		return true;
	for (int y = 0; y < this->_manageMap._map.getHeight(); ++y) {
		for (int x = 0; x < this->_manageMap._map.getWidth(); ++x) {
			if (this->_manageMap._map[y][x] ==
				MapPattern::WALKABLE ||
				this->_manageMap._map[y][x] ==
					MapPattern::TRAIL)
				walkableArea++;
		}
	}
	float percent = (int)(((float)walkableArea /
		(float)((this->_manageMap._map.getHeight() - 1) *
			(this->_manageMap._map.getWidth() - 1) - sizeMob)) *
		100);
	if (percent <= 70 && this->_patternQix == 0) {
		this->_listSharks.emplace_back(this->_manageMap, true);
		this->_patternQix = 1;
	} else if (percent <= 60 && this->_patternQix == 1) {
		this->_listSharks.emplace_back(this->_manageMap, false);
		this->_patternQix = 2;
	}
	this->_data.score = int((100 - percent) * 100);

	return (percent <= 25);
}