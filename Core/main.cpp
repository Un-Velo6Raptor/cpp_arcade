#include <Core.hpp>

/*
** EPITECH PROJECT, 2018
** cpp_arcade
** File description:
** Created by sahel.lucas-saoudi@epitech.eu,
*/

int main(int ac, char **av, char **env)
{
	if (ac != 2)
		return 1;
	(void) env;
	try {
		ar::Core core;
		core.start(av[1]);

	} catch (std::exception &e) {
		std::cerr << e.what() << std::endl;
		return 1;
	}
}