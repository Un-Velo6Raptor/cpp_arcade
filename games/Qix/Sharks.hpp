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

namespace ar {
	class ManageSharks {
	public:
		ManageSharks(ar::ManageMap &manageMap, bool randOk);
		~ManageSharks();

		int loopSharks(ar::ManageMap &);
		void setLastChar(ar::MapPattern);

		void setPosX(std::size_t);
		void setPosY(std::size_t);
		void setDir(ar::DirObj);

		std::size_t getPosX() const;
		std::size_t getPosY() const;
		ar::MapPattern getLastChar() const;

	private:
		void initSharksOnTheMap(ar::ManageMap &, bool);
		std::vector<DirObj> getAllDirSharks(ar::ManageMap &);
		int sharksEatPlayer(ar::ManageMap &manageMap);
		bool isAnotherTrailAround(ar::ManageMap &);
		int GetCharTo(ar::ManageMap &, int x, int y);

		// SharksIA
		ar::DirObj findTheDirToGo(ar::ManageMap &);
		ar::DirObj _dir;
		ar::MapPattern _lastChar;
		std::size_t _posX;
		std::size_t _posY;
	};
}

#endif //CPP_ARCADE_SHARKS_HPP
