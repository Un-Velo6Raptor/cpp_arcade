/*
** EPITECH PROJECT, 2018
** cpp_arcade
** File description:
** Created by martin.januario@epitech.eu,
*/

#include "RocketException.hpp"
#include "ManageRocket.hpp"

void ManageRocket::setDirection(DirectionObj dir)
{
	this->_dir = dir;
}

void ManageRocket::setPosX(double posX)
{
	this->_posX = posX;
}

void ManageRocket::setPosY(double posY)
{
	this->_posY = posY;
}

void ManageRocket::setSpeed(double speed)
{
	if (speed <= 0.00)
		throw RocketException("Speed of a rocket must be positiv",
			"Set speed");
	this->_speed = speed;
}