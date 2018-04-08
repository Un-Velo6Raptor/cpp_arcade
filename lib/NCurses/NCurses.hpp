//
// EPITECH PROJECT, 2018
// Arcade
// File description:
// nCurses class
//

#ifndef		NCURSES_HPP_
#define		NCURSES_HPP_

#include	<vector>
#include	<map>
#include	"Map.hpp"
#include	"IDisplay.hpp"

namespace ar {
	class NCurses : public ar::IDisplay {
	public:
		NCurses();
		~NCurses();

		ar::Event getEvent(int &realEvent);
		bool canHandleSprites();
		void displayGame(const ar::userInterface &UI, ar::Map &map);
		void loadResources(const std::map<unsigned char, ar::colorVector> &colors);
		void loadResources(const std::string &filePath, const std::map<unsigned char, ar::spriteCoords> &sprites);
		void initMenu(const std::vector<std::string> &menuChoices, const std::string &menuName, const std::vector<std::string> &display);
		int refreshMenu(const ar::Event &key, const std::vector<ar::userInterface> &dataArray);
		void refreshUsername(std::string &name, int realKey);
		void destroyMenu();

	private:
		int getMul(int width, int height, ar::Map &map);

		int getStartY(int width, int height, ar::Map &map);
		int getStartX(int width, int height, ar::Map &map);

		int findColorPair(int value);

		void displayMap(ar::Map &map, const int mul, const std::pair<int, int> start);
		void displayName(const int width) const;

		void printGameName(int &i, const int width, const std::string str) const;
		void printHighScore(const int width, const ar::userInterface ui) const;
		void printLibName(int &i, const int width, const std::string str) const;

		std::map<unsigned char, ar::colorVector> _colorLegend;

		std::vector<std::string> _menuChoices;
		std::string _menuName;
		std::vector<std::string> _display;

		int _selectedGame;

		std::string _username;
	};
}

#endif		/* !NCURSES_HPP_*/
