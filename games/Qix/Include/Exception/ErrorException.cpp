/*
** EPITECH PROJECT, 2018
** cpp_arcade
** File description:
** Created by martin.januario@epitech.eu,
*/

#include "ErrorException.hpp"

ErrorException::ErrorException(std::string const &message,
	std::string const &name
) : _message(message), _name(name)
{
}

const char *ErrorException::what() const noexcept
{
	return this->_message.c_str();
}

std::string const &ErrorException::getName() const
{
	return this->_name;
}