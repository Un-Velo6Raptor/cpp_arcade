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