/*
** EPITECH PROJECT, 2018
** cpp_arcade
** File description:
** Created by martin.januario@epitech.eu,
*/

#ifndef CPP_ARCADE_ERROREXCEPTION_HPP
# define CPP_ARCADE_ERROREXCEPTION_HPP

# include <string>
# include <iostream>

namespace ar {
	class ErrorException : public std::exception {
	public:
		ErrorException(std::string const &message,
			std::string const &name
		);

		// Member Functions
		std::string const &getName() const;

		const char *what() const noexcept override;

	private:
		std::string _message;
		std::string _name;
	};
}

#endif //CPP_ARCADE_ERROREXCEPTION_HPP
