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

		// Other
		void *sym(std::string const &symName);

	private:
		void *_dl = nullptr;
	};
}

#endif //CPP_ARCADE_LOADER_HPP
