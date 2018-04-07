/*
** EPITECH PROJECT, 2018
** cpp_arcade
** File description:
** Created by martin.januario@epitech.eu,
*/

#ifndef CPP_ARCADE_MAPEXCEPTION_HPP
# define CPP_ARCADE_MAPEXCEPTION_HPP

# include "ErrorException.hpp"

class MapException : public ErrorException {
	public:
	MapException(std::string const &message, std::string const &name);
};

#endif //CPP_ARCADE_MAPEXCEPTION_HPP
