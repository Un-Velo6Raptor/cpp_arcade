/*
** EPITECH PROJECT, 2018
** cpp_arcade
** File description:
** Created by martin.januario@epitech.eu,
*/

#include "RocketException.hpp"
#include "ManageRocket.hpp"

void ManageRocket::moveForwardRocket(void)
{
	if (this->_speed <= 0.00)
		throw RocketException("Speed of a rocket must be positiv",
			"Rocket constructor");

	switch (this->_dir) {
	case DirectionObj::RIGHT :
		this->_posX += this->_speed;
		break;
	case DirectionObj::LEFT :
		this->_posX -= this->_speed;
		break;
	case DirectionObj::DOWN :
		this->_posY += this->_speed;
		break;
	case DirectionObj::UP :
		this->_posY -= this->_speed;
		break;
	default:
		throw RocketException("A rocket need a direction for move", "moveForwardRocket");
	}
}