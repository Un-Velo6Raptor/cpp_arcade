/*
** EPITECH PROJECT, 2018
** cpp_arcade
** File description:
** Created by martin.januario@epitech.eu,
*/

#ifndef CPP_ARCADE_ENEMYEXCEPTION_HPP
# define CPP_ARCADE_ENEMYEXCEPTION_HPP

# include "ErrorException.hpp"

class EnemyException : public ErrorException {
	public:
	EnemyException(std::string const &message, std::string const &name);
};

#endif //CPP_ARCADE_ENEMYEXCEPTION_HPP
