/*
** EPITECH PROJECT, 2018
** cpp_arcade
** File description:
** Created by martin.januario@epitech.eu,
*/

#ifndef CPP_ARCADE_ROCKETEXCEPTION_HPP
# define CPP_ARCADE_ROCKETEXCEPTION_HPP

# include "ErrorException.hpp"

class RocketException : public ErrorException {
	public:
	RocketException (std::string const &message, std::string const &name);
};

#endif //CPP_ARCADE_ROCKETEXCEPTION_HPP
