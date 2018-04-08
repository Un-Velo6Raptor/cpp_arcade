/*
** EPITECH PROJECT, 2018
** cpp_arcade
** File description:
** Created by sahel.lucas-saoudi@epitech.eu,
*/

#ifndef CPP_ARCADE_CORE_HPP
#define CPP_ARCADE_CORE_HPP

#include <iostream>
#include <vector>
#include "IDisplay.hpp"
#include "IGame.hpp"
#include "DLoader.hpp"

namespace ar {
	class Core {
	public:
		// Constructor
		Core();

		// Destructor
		~Core();

		// Operator

		// Getter

		// Setter

		// Other
		void start(std::string const &defaultPath);
		void exit();
		void restart();

	protected:

	private:
		std::vector<std::string> const getAllFileOfDirWithPath(std::string const &path);
		void loadGraphicalsLib(std::vector<std::string> const &paths);
		void loadGamesLib(std::vector<std::string> const &paths);

		std::vector<std::string> getGamesName();

		void changeGameLib(int idx);
		void changeGraphicalLib(int idx);
		void destroyActualGame();
		void destroyActualGraphical();

		void loadSpritesAndColors();

		void refreshUserInterface();

		void nextGraphicalLib();
		void prevGraphicalLib();
		void nextGameLib();
		void prevGameLib();

		void activateMenu();

		void manageMenu(ar::Event &event, int key);
		void manageGame(ar::Event &event);

		int _graphicalsIdx = 0;
		int _gamesIdx = 0;

		std::vector<ar::DLoader *> _gamesDL;
		std::vector<ar::DLoader *> _graphicalsDL;

		ar::IDisplay *_graphical = nullptr;
		ar::IGame *_game = nullptr;

		bool _ended = false;
		bool _menu = true;

		std::vector<ar::userInterface> _userInterfaces;
		ar::userInterface _actualUser = {0, "", 0};

		std::vector<std::string> _gamesName;
		std::vector<std::string> _graphicalsName;

		std::string _username = "";

		std::map<ar::Event, void (ar::Core::*)()> _actions = {
			{ar::Event::AR_PREV_GRAPH_LIB, &ar::Core::prevGraphicalLib},
			{ar::Event::AR_NEXT_GRAPH_LIB, &ar::Core::nextGraphicalLib},
			{ar::Event::AR_PREV_GAME, &ar::Core::prevGameLib},
			{ar::Event::AR_NEXT_GAME, &ar::Core::nextGameLib},
			{ar::Event::AR_MENU, &ar::Core::activateMenu},
			{ar::Event::AR_EXIT, &ar::Core::exit},
			{ar::Event::AR_RESTART, &ar::Core::restart}
		};
	};
}

#endif //CPP_ARCADE_CORE_HPP
