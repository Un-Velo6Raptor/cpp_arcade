/*
** EPITECH PROJECT, 2018
** cpp_arcade
** File description:
** Created by martin.januario@epitech.eu,
*/

#include "AbstractHitBox.hpp"

AbstractHitBox::AbstractHitBox(std::size_t sizeX, std::size_t sizeY) : _sizeX(sizeX), _sizeY(sizeY)
{
}

std::size_t AbstractHitBox::getSizeY() const
{
	return this->_sizeY;
}

std::size_t AbstractHitBox::getSizeX() const
{
	return this->_sizeX;
}

void AbstractHitBox::setSizeX(std::size_t sizeX)
{
	this->_sizeX = sizeX;
}

void AbstractHitBox::setSizeY(std::size_t sizeY)
{
	this->_sizeY = sizeY;
}