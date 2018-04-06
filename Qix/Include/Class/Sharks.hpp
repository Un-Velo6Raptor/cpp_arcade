/*
** EPITECH PROJECT, 2018
** cpp_arcade
** File description:
** Created by martin.januario@epitech.eu,
*/

#ifndef CPP_ARCADE_SHARKS_HPP
# define CPP_ARCADE_SHARKS_HPP

# include <cstdlib>
# include "Enum.hpp"
# include "ManageMap.hpp"

class ManageSharks {
	public:
	ManageSharks(ManageMap &manageMap);
	~ManageSharks();

	int loopSharks(ManageMap &, std::size_t, std::size_t);

	protected:

	private:
	void initSharksOnTheMap(ManageMap &);

	// SharksIA
	DirObj findTheDirToGo(ManageMap &, std::size_t, std::size_t);

	DirObj _dir; // Is the dir where the sharks can't go
	std::size_t _posX;
	std::size_t _posY;
};

#endif //CPP_ARCADE_SHARKS_HPP
