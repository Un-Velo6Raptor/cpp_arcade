/*
** EPITECH PROJECT, 2018
** cpp_arcade
** File description:
** Created by martin.januario@epitech.eu,
*/

#ifndef CPP_ARCADE_MANAGEMAP_HPP
# define CPP_ARCADE_MANAGEMAP_HPP

# include <iostream>
# include <string>
# include <map>

enum MapChar {
	Empty = ' ',
	Corner = '+',
	Vertical = '|',
	Horizontal = '-',
	ObjectToTake = 'o',
};

class ManageMap {
	public:
	// Constructor / destructor
	ManageMap(const unsigned int &mapSizeX, const unsigned int &mapSizeY);
	~ManageMap();

	// Copy constructor and operator copy // Todo: need an Update
	ManageMap(const ManageMap &other);
	ManageMap &operator=(ManageMap &other);

	void displayMap(void) const;
	void resetMap(void);
	void generateMap(unsigned int percent);

	void generateMiddleLine(unsigned int line);
	void generateFirstLine(unsigned int line);
	void createLine(unsigned int index_y);

	// Setter

	// Getter
	unsigned int getSizeX(void) const;
	unsigned int getSizeY(void) const;

	protected:

	private:
	int placePowerUp(std::size_t nbPowerUp);

	unsigned int _sizeX;
	unsigned int _sizeY;

	std::map<unsigned int, std::string> _map;
};

#endif //CPP_ARCADE_MANAGEMAP_HPP
