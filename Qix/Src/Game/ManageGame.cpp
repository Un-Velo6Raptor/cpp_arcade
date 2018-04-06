/*
** EPITECH PROJECT, 2018
** cpp_arcade
** File description:
** Created by martin.januario@epitech.eu,
*/

#include "Game.hpp"

// Todo: Ajouter le timer
void ar::Qix::loop() // Todo: A faire
{
	if (this->_isPaused)
		return;
	moovePlayer();
	randomMoveQix();

	for (auto it = this->_listSharks.begin(); it != this->_listSharks.end() ; ++it) {
		(*it)->loopSharks(this->_manageMap, this->_lastBorderPosX, this->_lastBorderPosY);
	}
}

void ar::Qix::setPause()
{
	this->_isPaused = true;
}

bool ar::Qix::isGameOver() // todo A faire
{
	return (!this->_life);
}