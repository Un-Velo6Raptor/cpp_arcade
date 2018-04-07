/*
** EPITECH PROJECT, 2018
** cpp_arcade
** File description:
** Created by martin.januario@epitech.eu,
*/

#ifndef CPP_ARCADE_SHARKS_HPP
# define CPP_ARCADE_SHARKS_HPP

# include <vector>
# include <cstdlib>
# include "Enum.hpp"
# include "ManageMap.hpp"

class ManageSharks {
	public:
	ManageSharks(ManageMap &manageMap, bool randOk);
	~ManageSharks();

	int loopSharks(ManageMap &);

	void setLastChar(MapPattern);
	void setPosX(std::size_t);
	void setPosY(std::size_t);
	void setDir(DirObj);

	std::size_t getPosX() const;
	std::size_t getPosY() const;
	MapPattern getLastChar() const;

	protected:

	private:
	void initSharksOnTheMap(ManageMap &, bool);
	std::vector<DirObj> getAllDirSharks(ManageMap &);
	int sharksEatPlayer(ManageMap &manageMap);

	// SharksIA
	DirObj findTheDirToGo(ManageMap &);

	DirObj _dir;
	MapPattern _lastChar;
	std::size_t _posX;
	std::size_t _posY;
};

#endif //CPP_ARCADE_SHARKS_HPP
