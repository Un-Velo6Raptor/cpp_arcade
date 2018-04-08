/*
** EPITECH PROJECT, 2018
** cpp_arcade
** File description:
** Created by sahel.lucas-saoudi@epitech.eu,
*/

#include <iostream>
#include "Core.hpp"

bool envError()
{
	if (!getenv("DISPLAY")) {
		std::cerr << "Env variable Display is not set" << std::endl;
		return true;
	}
	return false;
}

int main(int ac, char **av)
{
	if (ac != 2) {
		std::cerr << "USAGE" << std::endl;
		std::cerr << "\t " + std::string(av[0]);
		std::cerr << " [ path to a graphics library ]" << std::endl << std::endl;
		std::cerr << "DESCRIPTION" << std::endl;
		std::cerr << "\tAllows you to play to several arcade games." << std::endl;
		return 84;
	}
	if (envError()) {
		std::cerr << "Please stop doing unconventional action." << std::endl;
		return 84;
	}
	try {
		ar::Core core;
		core.start(av[1]);

	} catch (std::exception &e) {
		std::cerr << e.what() << std::endl;
		return 84;
	}
	return 0;
}
