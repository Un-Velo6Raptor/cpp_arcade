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
}

void ar::Qix::setPause()
{
	this->_isPaused = true;
}

bool ar::Qix::isGameOver() // todo A faire
{
	return (!this->_life);
}