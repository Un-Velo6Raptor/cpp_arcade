/*
** EPITECH PROJECT, 2018
** cpp_arcade
** File description:
** Created by martin.januario@epitech.eu,
*/

#ifndef CPP_ARCADE_MANAGEMAP_HPP
# define CPP_ARCADE_MANAGEMAP_HPP

# include <iostream>
# include <map>
# include "Map.hpp"

class ManageMap {
	public:
	// Constructor & destructor
	ManageMap(int height, int width);
	~ManageMap() = default;

	// Basics map
	void DisplayMap(void);

	ar::Map _map;

	protected:

	private:
	// Init map
	void InitMap(void);
	void InitMapBorder(void);
	void PrintLine(int index, bool opt);
	int PlaceQixOntTheMap(std::size_t pattern);

	std::map<std::size_t, std::string> _qixPattern; // Size of 8x8
	std::size_t _posQixX;
	std::size_t _posQixY;
};

#endif //CPP_ARCADE_MANAGEMAP_HPP
