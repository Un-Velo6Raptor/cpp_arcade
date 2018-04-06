/*
** EPITECH PROJECT, 2018
** cpp_arcade
** File description:
** Created by sahel.lucas-saoudi@epitech.eu,
*/

#include <iostream>
#include "Core.hpp"

int main(int ac, char **av, char **env)
{
	if (ac != 2) {
		std::cerr << "USAGE" << std::endl;
		std::cerr << "\t " + std::string(av[0]);
		std::cerr << " [ path to a graphics library ]\n" << std::endl;
		std::cerr << "DESCRIPTION" << std::endl;
		std::cerr << "\tAllows you to play to several arcade games." << std::endl;
		return 84;
	}
	(void) env;
	try {
		ar::Core core;
		core.start(av[1]);

	} catch (std::exception &e) {
		std::cerr << e.what() << std::endl;
		return 84;
	}
	return 0;
}
