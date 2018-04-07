/*
** EPITECH PROJECT, 2018
** cpp_arcade
** File description:
** Created by martin.januario@epitech.eu,
*/

#include "Game.hpp"

const std::map<unsigned char, ar::colorVector> &ar::Qix::getColors() const
{
	return this->_colors;
}

ar::Map &ar::Qix::getMap()
{
	_behindPlayer = (MapPattern)(this->_manageMap._map[this->_manageMap._map.getPlayerY()][this->_manageMap._map.getPlayerX()]);
	this->_manageMap._map[this->_manageMap._map.getPlayerY()][this->_manageMap._map.getPlayerX()] = MapPattern::PLAYER;
	const std::string red("\033[0;31m");
	const std::string green("\033[1;32m");
	const std::string yellow("\033[1;33m");
	const std::string cyan("\033[0;36m");
	const std::string magenta("\033[0;35m");
	const std::string reset("\033[0m");
/*
	for (int idx = 0; this->_manageMap._map[idx]; ++idx) {
		for (int x = 0; x < this->_manageMap._map.getWidth(); ++x) {
			std::cerr << reset;
			switch (this->_manageMap._map[idx][x]) {
			case MapPattern::QIX :
				std::cerr << red;
				break;
			case MapPattern::BORDER :
				std::cerr << green;
				break;
			case MapPattern::TRAIL :
				std::cerr << cyan;
				break;
			case MapPattern::OLDBORDER :
				std::cerr << yellow;
				break;
			case MapPattern::SHARKS :
				std::cerr << red;
				break;
			}
			if (idx == this->_manageMap._map.getPlayerY() && x == this->_manageMap._map.getPlayerX())
				std::cerr << reset << magenta;
			std::cerr << this->_manageMap._map[idx][x];
		}
		std::cerr << std::endl;
	}
 */
	return this->_manageMap._map;
}

const std::string ar::Qix::getGameName() const
{
	return "Qix";
}

const std::string ar::Qix::getSpritesPath() const
{
	return this->_spritePath;
}

const std::map<unsigned char, ar::spriteCoords> &ar::Qix::getSprites() const
{
	return this->_sprites;
}

std::size_t ar::Qix::getLife() const
{
	return this->_life;
}

int ar::Qix::getLastBorderPosX() const
{
	return this->_lastBorderPosX;
}

int ar::Qix::getLastBorderPosY() const
{
	return this->_lastBorderPosY;
}