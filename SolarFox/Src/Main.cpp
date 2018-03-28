/*
** EPITECH PROJECT, 2018
** cpp_arcade
** File description:
** Created by martin.januario@epitech.eu,
*/

#include "MapException.hpp"
#include "ManageMap.hpp"

int main(void)
{
	ManageMap tmp(10, 10);

	try {
		tmp.generateMap(20);
	} catch (MapException const &error) {
		std::cout << "From " << error.getName() << ":" << std::endl;
		std::cout << error.what() << std::endl;
		return 84;
	}
	tmp.displayMap();
	return (0);
}