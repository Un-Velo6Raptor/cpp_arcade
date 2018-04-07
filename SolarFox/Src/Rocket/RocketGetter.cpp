/*
** EPITECH PROJECT, 2018
** cpp_arcade
** File description:
** Created by martin.januario@epitech.eu,
*/

#include "ManageRocket.hpp"

DirectionObj ManageRocket::getDirection() const
{
	return this->_dir;
}

double ManageRocket::getPosX() const
{
	return this->_posX;
}

double ManageRocket::getPosY() const
{
	return this->_posY;
}

double ManageRocket::getSpeed() const
{
	return this->_speed;
}