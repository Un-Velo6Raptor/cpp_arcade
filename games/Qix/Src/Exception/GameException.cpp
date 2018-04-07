/*
** EPITECH PROJECT, 2018
** cpp_arcade
** File description:
** Created by martin.januario@epitech.eu,
*/

#include "GameException.hpp"

GameException::GameException(std::string const &message, std::string const &name
) : ErrorException(message, name)
{
}