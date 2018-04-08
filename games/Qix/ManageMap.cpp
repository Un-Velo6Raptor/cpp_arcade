/*
** EPITECH PROJECT, 2018
** cpp_arcade
** File description:
** Created by martin.januario@epitech.eu,
*/

#include "MapException.hpp"
#include "ManageMap.hpp"
#include "Enum.hpp"

ar::ManageMap::ManageMap(int height, int width) : _map(width, height)
{
	if (height <= 25 || width <= 25)
		throw ar::MapException("The minimum map size is (10, 10)",
			"Constructor");
	this->_posQixX = (std::size_t)width / 2 - 4;
	this->_posQixY = (std::size_t)height / 2 - 4;
	this->_qixPattern.insert({0, " *    * "
				     "  ****  "
				     " ****** "
				     "** ** **"
				     "********"
				     " **  ** "
				     "* *  * *"
				     "*      *"});
	this->_qixPattern.insert({1, "  *  *  "
				     " *    * "
				     "  *  *  "
				     " ****** "
				     "*  **  *"
				     "********"
				     " **  ** "
				     "* *  * *"});
	this->_qixPattern.insert({2, "***  ***"
				     " *    * "
				     "***  ***"
				     " ****** "
				     "*  **  *"
				     "********"
				     " ****** "
				     "* *  * *"});
	InitMap();
}

void ar::ManageMap::PrintLine(int index, bool opt)
{
	for (int i = 0; i < this->_map.getWidth(); ++i) {
		if (opt || i == 0 || i == this->_map.getWidth() - 1)
			this->_map[index][i] = ar::MapPattern::BORDER;
	}
}

void ar::ManageMap::InitMapBorder(void)
{
	for (int idx = 0; idx < this->_map.getHeight(); ++idx) {
		if (!idx || idx == this->_map.getHeight() - 1)
			PrintLine(idx, true);
		else
			PrintLine(idx, false);
	}
}

int ar::ManageMap::PlaceQixOntTheMap(std::size_t pattern)
{
	for (int idx_y = 0; this->_map[idx_y] ; ++idx_y) {
		for (int idx_x = 0; idx_x < this->_map.getWidth(); ++idx_x) {
			this->_map[idx_y][idx_x] = (this->_map[idx_y][idx_x] == MapPattern::QIX) ? MapPattern::WALKABLE : this->_map[idx_y][idx_x];
		}
	}
	std::size_t cpt_line = 0;
	bool check = false;
	for (std::size_t i = 0; this->_qixPattern[pattern].size() != i ; ++i) {
		if (i && !(i % 8))
			cpt_line++;
		if (this->_map[this->_posQixY + cpt_line][this->_posQixX + (i % 8)] != MapPattern::WALKABLE)
			check = true;
		if (this->_map[this->_posQixY + cpt_line][this->_posQixX + (i % 8)] == MapPattern::TRAIL)
			return (-1);
		if (!check && this->_qixPattern[pattern][i] == '*')
			this->_map[this->_posQixY + cpt_line][this->_posQixX + (i % 8)] = MapPattern::QIX;
	}
	return (int)check;
}

void ar::ManageMap::InitMap(void)
{
	InitMapBorder();
	if (PlaceQixOntTheMap(0) != 0)
		throw MapException("Can't place Qix on the map", "Init map");

}