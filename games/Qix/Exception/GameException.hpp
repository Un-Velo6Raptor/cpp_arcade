/*
** EPITECH PROJECT, 2018
** cpp_arcade
** File description:
** Created by martin.januario@epitech.eu,
*/

#ifndef CPP_ARCADE_GAMEEXCEPTION_HPP
# define CPP_ARCADE_GAMEEXCEPTION_HPP

# include "ErrorException.hpp"

namespace ar {
	class GameException : public ErrorException {
		public:
		GameException(std::string const &message,
			std::string const &name
		);
	};
}

#endif //CPP_ARCADE_GAMEEXCEPTION_HPP
