/*
** EPITECH PROJECT, 2018
** cpp_arcade
** File description:
** Created by martin.januario@epitech.eu,
*/

#include <cstdlib>
#include "MapException.hpp"
#include "ManageMap.hpp"

int ManageMap::placePowerUp(std::size_t nbPowerUp)
{
	if (!nbPowerUp)
		return (0);
	for (unsigned int idx_y = 3;
		idx_y < this->_sizeY - 3 && nbPowerUp; ++idx_y) {
		for (unsigned int idx_x = 3;
			idx_x < this->_sizeX - 3 && nbPowerUp; ++idx_x) {
			if (!(std::rand() % 4)) {
				this->_map[idx_y][idx_x] = MapChar::ObjectToTake;
				nbPowerUp--;
			}
		}
	}
	return (placePowerUp(nbPowerUp));
}

void ManageMap::generateMap(unsigned int percent)
{
	if (percent < 20)
		throw MapException("Percent too tiny, need more than 20%",
			"CreatePowerUp");
	resetMap();
	auto nbPowerUp = (std::size_t)(
		((double)((this->_sizeY - 6) * (this->_sizeX - 6))) / 100 *
			(double)percent);
	placePowerUp(nbPowerUp);
}