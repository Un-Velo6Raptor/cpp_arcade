/*
** EPITECH PROJECT, 2021
** arcade
** File description:
** display interface
*/

#ifndef CPP_ARCADE_IDISPLAY_HPP
# define CPP_ARCADE_IDISPLAY_HPP

#include <map>
#include <vector>
#include "Arcade.hpp"
#include "Map.hpp"

namespace ar {
	class IDisplay {
	public:
		virtual ~IDisplay() = default;
		virtual ar::Event getEvent(int &realEvent) = 0;

		virtual bool canHandleSprites() = 0;
		virtual void displayGame(const userInterface &UI, Map &map) = 0;
		virtual void loadResources(const std::map<unsigned char, colorVector> &colors) = 0;
		virtual void loadResources(const std::string &filePath,
			const std::map<unsigned char, spriteCoords> &sprites) = 0;
		virtual void initMenu(const std::vector<std::string> &menuChoices,
				      const std::string &menuName,
				      const std::vector<std::string> &display) = 0;
		virtual int refreshMenu(const ar::Event &key,
					const std::vector<userInterface> &dataArray) = 0;
		virtual void refreshUsername(std::string &name, int realKey) = 0;
		virtual void destroyMenu() = 0;
	};

	typedef ar::IDisplay *createDisplay();
	typedef void destroyDisplay(ar::IDisplay *);
};

#endif //CPP_ARCADE_IDISPLAY_HPP
