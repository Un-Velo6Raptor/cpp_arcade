/*
** EPITECH PROJECT, 2018
** cpp_arcade
** File description:
** Created by martin.januario@epitech.eu,
*/

#include "MapException.hpp"

ar::MapException::MapException(std::string const &message, std::string const &name) : ErrorException(message, name)
{
}