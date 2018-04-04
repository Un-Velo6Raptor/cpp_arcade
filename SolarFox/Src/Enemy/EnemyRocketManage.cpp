/*
** EPITECH PROJECT, 2018
** cpp_arcade
** File description:
** Created by martin.januario@epitech.eu,
*/

#include "RocketException.hpp"
#include "EnemyException.hpp"
#include "ManageEnemy.hpp"

DirectionObj ManageEnemy::OrientateRocketLauncher(void)
{
	DirectionObj result = DirectionObj::UNKNOWN;

	if (this->_mapGame->getMap()[(std::size_t)_posY][(std::size_t)_posX] == MapChar::Horizontal)
		result = ((std::size_t)this->_posY == 0) ? DirectionObj::DOWN : DirectionObj::UP;
	else if (this->_mapGame->getMap()[(std::size_t)_posY][(std::size_t)_posX] == MapChar::Vertical)
		result = ((std::size_t)this->_posX == 0) ? DirectionObj::RIGHT : DirectionObj::LEFT;
	else
		throw EnemyException("Can't Orientate the rocket launcher", "OrientateRocketLauncher");

	return result;
}

void ManageEnemy::LaunchRocket(void)
{
	if (this->_dirRocket == DirectionObj::UNKNOWN)
		this->_dirRocket = OrientateRocketLauncher();

	try {
		this->_rocketFire.push_back(new ManageRocket(this->_posX, this->_posY, 0.1, this->_dirRocket));
	} catch (RocketException const &error) {
		throw EnemyException(error.what(), "Launch Rocket EnemyManage");
	}
}

void ManageEnemy::AdvanceAllRocket()
{
	for (auto it = this->_rocketFire.begin(); it != this->_rocketFire.end() ; ++it) {
		(*it)->moveForwardRocket();
	}
}