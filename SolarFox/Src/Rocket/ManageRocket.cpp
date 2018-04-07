/*
** EPITECH PROJECT, 2018
** cpp_arcade
** File description:
** Created by martin.januario@epitech.eu,
*/

#include "RocketException.hpp"
#include "ManageRocket.hpp"

ManageRocket::ManageRocket(double posX, double posY, double speed,
	DirectionObj dir) : AbstractHitBox(8, 4), _posX(posX), _posY(posY),
	_speed(speed), _dir(dir)
{
	if (speed <= 0.00)
		throw RocketException("Speed of a rocket must be positiv",
			"Rocket constructor");
	if (dir == UP || dir == DOWN) {
		std::size_t tmp = this->getSizeX();
		this->setSizeX(this->getSizeY());
		this->setSizeY(tmp);
	}
}

ManageRocket::ManageRocket(const ManageRocket &other) : AbstractHitBox(other.getSizeX(), other.getSizeY())
{
	this->_posX = other._posX;
	this->_posY = other._posY;
	this->_speed = other._speed;
	this->_dir = other._dir;
}

ManageRocket &ManageRocket::operator=(const ManageRocket &other)
{
	this->_posX = other._posX;
	this->_posY = other._posY;
	this->_speed = other._speed;
	this->_dir = other._dir;
	this->setSizeY(other.getSizeY());
	this->setSizeX(other.getSizeX());
	return *this;
}