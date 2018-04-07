/*
** EPITECH PROJECT, 2018
** cpp_arcade
** File description:
** Created by martin.januario@epitech.eu,
*/

#include "Game.hpp"

int ar::Qix::refreshScore() // TODO: A faire
{
	return this->_data.score;
}

int ar::Qix::refreshTimer() // TODO: A faire
{
	int	newTime;

	if (_isPaused == true && _startPause == -1) {
		_startPause = clock();
	} else if (_isPaused == true) {
		if (clock() - _startPause > 1000000) {
			_startPause = clock();
			_timer++;
		}
	} else if (_startPause != -1) {
		_startPause = -1;
	}
	newTime = std::time(nullptr) - _timer;
	if (newTime >= _tmpTimer && _isPaused == false)
		_tmpTimer = newTime;
	return _tmpTimer;
}