/*
** EPITECH PROJECT, 2018
** cpp_arcade
** File description:
** Created by martin.januario@epitech.eu,
*/

#include "GameException.hpp"
#include "Game.hpp"

void ar::Qix::KeyUpPressed(void)
{
	this->_isPlayerStopped = (this->_actualDir == DirObj::DOWN);
	this->_actualDir = DirObj::UP;
}

void ar::Qix::KeyDownPressed(void)
{
	this->_isPlayerStopped = (this->_actualDir == DirObj::UP);
	this->_actualDir = DirObj::DOWN;
}

void ar::Qix::KeyLeftPressed(void)
{
	this->_isPlayerStopped = (this->_actualDir == DirObj::RIGHT);
	this->_actualDir = DirObj::LEFT;
}

void ar::Qix::KeyRightPressed(void)
{
	this->_isPlayerStopped = (this->_actualDir == DirObj::LEFT);
	this->_actualDir = DirObj::RIGHT;
}

void ar::Qix::manageKey(const ar::Event &key)
{
	static void (ar::Qix::*keyPressed[4])(void) = {&ar::Qix::KeyUpPressed,
		&ar::Qix::KeyDownPressed, &ar::Qix::KeyLeftPressed,
		&ar::Qix::KeyRightPressed};

	if (key == Event::AR_PAUSE)
		this->_isPaused = false;
	else if (this->_isPaused)
		return;
	else // TODO: Demander si on ne recevra bien que les touches de déplacements ou de pause uniquement
		(this->*keyPressed[key])();
}