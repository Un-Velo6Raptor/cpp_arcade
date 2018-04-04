/*
** EPITECH PROJECT, 2018
** cpp_arcade
** File description:
** Created by sahel.lucas-saoudi@epitech.eu,
*/

#ifndef CPP_ARCADE_LOADER_HPP
#define CPP_ARCADE_LOADER_HPP

#include <iostream>
#include <string>

namespace ar {

	class DLoader {
	public:
		// Constructor
		DLoader(std::string const &path);

		// Destructor
		~DLoader();

		// Operator

		// Getter
		std::string const &getName() const;

		// Setter
		void setName(std::string const &name);

		// Other
		void *sym(std::string const &symName);

	protected:

	private:
		void *_dl = nullptr;
		std::string _name;

	};
}

#endif //CPP_ARCADE_LOADER_HPP
