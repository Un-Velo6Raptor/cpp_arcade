/*
** EPITECH PROJECT, 2018
** cpp_arcade
** File description:
** Created by martin.januario@epitech.eu,
*/

#include "EnemyException.hpp"
#include "ManageEnemy.hpp"

DirectionObj ManageEnemy::OrientateTheDirEnemy(void)
{
	DirectionObj result = DirectionObj::UNKNOWN;

	if (this->_mapGame->getMap()[(std::size_t)_posY][(std::size_t)_posX] == MapChar::Vertical)
		result = DirectionObj::DOWN;
	else if (this->_mapGame->getMap()[(std::size_t)_posY][(std::size_t)_posX] == MapChar::Horizontal)
		result = DirectionObj::RIGHT;
	else
		throw EnemyException("Can't Orientate this enemy launcher", "OrientateRocketLauncher");

	return result;
}

void ManageEnemy::MoveHorizontaly(void)
{
	if (this->_dirEnemyMove == DirectionObj::LEFT)
		this->_posX -= this->_speed;
	else
		this->_posX += this->_speed;
	if (this->_posX <= 1 || (std::size_t)this->_posX >= this->_mapGame->getSizeX() - 1) {
		this->_dirEnemyMove = (this->_dirEnemyMove == DirectionObj::LEFT) ? DirectionObj::RIGHT : DirectionObj::LEFT;
		MoveHorizontaly();
	}
}

void ManageEnemy::MoveVerticaly(void)
{
	if (this->_dirEnemyMove == DirectionObj::UP)
		this->_posY -= this->_speed;
	else
		this->_posY += this->_speed;
	if (this->_posY <= 1 || (std::size_t)this->_posY >= this->_mapGame->getSizeY() - 1) {
		this->_dirEnemyMove = (this->_dirEnemyMove == DirectionObj::UP) ? DirectionObj::DOWN : DirectionObj::UP;
		MoveVerticaly();
	}
}

void ManageEnemy::FollowTheRail(void)
{
	if (this->_dirEnemyMove == DirectionObj::UNKNOWN)
		this->_dirEnemyMove =  OrientateTheDirEnemy();
	if (this->_dirEnemyMove == DirectionObj::LEFT || this->_dirEnemyMove == DirectionObj::RIGHT)
		MoveHorizontaly();
	else if (this->_dirEnemyMove == DirectionObj::UP || this->_dirEnemyMove == DirectionObj::DOWN)
		MoveVerticaly();
}