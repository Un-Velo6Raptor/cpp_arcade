/*
** EPITECH PROJECT, 2018
** cpp_arcade
** File description:
** Created by martin.januario@epitech.eu,
*/

#include "Game.hpp"

int ar::Qix::QixToDown(void)
{
	std::size_t posTmp = this->_manageMap._posQixY;

	this->_manageMap._posQixY += 1;
	int ret = this->_manageMap.PlaceQixOntTheMap(0);

	if (ret == -1) {
		return 1;
	} else if (ret) {
		this->_manageMap._posQixY = posTmp;
		this->_manageMap.PlaceQixOntTheMap(0);
	}
	return 0;
}

int ar::Qix::QixToUp(void)
{
	std::size_t posTmp = this->_manageMap._posQixY;

	this->_manageMap._posQixY -= 1;
	int ret = this->_manageMap.PlaceQixOntTheMap(0);

	if (ret == -1) {
		return 1;
	} else if (ret) {
		this->_manageMap._posQixY = posTmp;
		this->_manageMap.PlaceQixOntTheMap(0);
	}
	return 0;
}

int ar::Qix::QixToLeft(void)
{
	std::size_t posTmp = this->_manageMap._posQixX;

	this->_manageMap._posQixX -= 1;
	int ret = this->_manageMap.PlaceQixOntTheMap(0);

	if (ret == -1) {
		return 1;
	} else if (ret) {
		this->_manageMap._posQixX = posTmp;
		this->_manageMap.PlaceQixOntTheMap(0);
	}
	return 0;
}

int ar::Qix::QixToRight(void)
{
	std::size_t posTmp = this->_manageMap._posQixX;

	this->_manageMap._posQixX += 1;
	int ret = this->_manageMap.PlaceQixOntTheMap(0);

	if (ret == -1) {
		return 1;
	} else if (ret) {
		this->_manageMap._posQixX = posTmp;
		this->_manageMap.PlaceQixOntTheMap(0);
	}
	return 0;
}

int ar::Qix::randomMoveQix(void)
{
	static int (ar::Qix::*MoveQixTo[4])(void) = {&ar::Qix::QixToLeft,
		&ar::Qix::QixToRight, &ar::Qix::QixToDown, &ar::Qix::QixToUp};
	int dir = rand() % 4;

	if ((this->*MoveQixTo[dir])() == 1) {
		this->_life -= 1;
		resetSpecificCharMap(MapPattern::TRAIL);
		this->_manageMap._map.setPlayerY(this->_lastBorderPosY);
		this->_manageMap._map.setPlayerX(this->_lastBorderPosX);
	}
	return (0);
}