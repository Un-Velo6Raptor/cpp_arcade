/*
** EPITECH PROJECT, 2018
** cpp_arcade
** File description:
** Created by martin.januario@epitech.eu,
*/

#include "EnemyException.hpp"
#include "ManageEnemy.hpp"

ManageEnemy::ManageEnemy(ManageMap *mapGame, double posX, double posY, double speed, std::size_t rateOfFire
) : AbstractHitBox(10, 15), _mapGame(mapGame), _dirEnemyMove(DirectionObj::UNKNOWN), _posX(posX), _posY(posY),
	_speed(speed), _rateOfFire(rateOfFire)
{
	if (speed <= 0 || posX < 0 || posY < 0 || !rateOfFire)
		throw EnemyException("Speed, posX, posY, rateOfFire must be positiv",
			"Constructor Manage Enemy");
	if (posX >= mapGame->getSizeX() || posY >= mapGame->getSizeY())
		throw EnemyException("This enemy is not in the map",
			"Constructor Manage Enemy");
	if (this->_mapGame->getMap()[(std::size_t)posY][(std::size_t)posX] != MapChar::Vertical &&
		this->_mapGame->getMap()[(std::size_t)posY][(std::size_t)posX] != MapChar::Horizontal)
		throw EnemyException(
			"This enemy must be place on '|' or on a '-'",
			"Constructor Manage Enemy");
	if (this->_mapGame->getMap()[(std::size_t)posY][(std::size_t)posX] == MapChar::Horizontal) {
		std::size_t tmp = this->getSizeX();
		this->setSizeX(this->getSizeY());
		this->setSizeY(tmp);
	}
	this->_dirRocket = DirectionObj::UNKNOWN;
}

ManageEnemy::ManageEnemy(ManageEnemy &other) : AbstractHitBox(other.getSizeX(), other.getSizeY())
{
	this->_speed = other._speed;
	this->_posY = other._posY;
	this->_posX = other._posX;
	this->_mapGame = other._mapGame;
	this->_rateOfFire = other._rateOfFire;
	this->_dirRocket = other._dirRocket;
	this->_dirEnemyMove = other._dirEnemyMove;
}

ManageEnemy &ManageEnemy::operator=(ManageEnemy &other)
{
	this->_speed = other._speed;
	this->_posY = other._posY;
	this->_posX = other._posX;
	this->_mapGame = other._mapGame;
	this->_rateOfFire = other._rateOfFire;
	this->_dirRocket = other._dirRocket;
	this->_dirEnemyMove = other._dirEnemyMove;

	this->setSizeY(other.getSizeY());
	this->setSizeX(other.getSizeX());
	return *this;
}

ManageEnemy::~ManageEnemy()
{
	for (auto it = this->_rocketFire.begin(); it != this->_rocketFire.end() ; ++it) {
		delete(*it);
	}
}