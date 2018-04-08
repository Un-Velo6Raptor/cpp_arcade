/*
** EPITECH PROJECT, 2018
** cpp_arcade
** File description:
** Created by sahel.lucas-saoudi@epitech.eu,
*/

#include <dirent.h>
#include <cstring>
#include "Core.hpp"
#include "Config.hpp"

ar::Core::Core()
{
	loadGraphicalsLib(getAllFileOfDirWithPath(GRAPHICALS_PATH));
	loadGamesLib(getAllFileOfDirWithPath(GAMES_PATH));

	if (_graphicalsDL.empty() ||
		_gamesDL.empty()) {
		throw std::runtime_error("Arcade need at least one Gaming lib and one Graphical Lib");
	}
}

ar::Core::~Core()
{
	for (auto &it: _graphicalsDL) {
		delete it;
	}
	for (auto &it: _gamesDL) {
		delete it;
	}
}

std::vector<std::string> const ar::Core::getAllFileOfDirWithPath(std::string const &path)
{
	DIR *directory = opendir(path.c_str());
	std::vector<std::string> files;

	if (directory) {
		dirent *de = readdir(directory);
		while (de) {
			if (strcmp(de->d_name, ".") != 0 &&
				strcmp(de->d_name, "..") != 0 &&
				de->d_type != DT_DIR && !strncmp(de->d_name, LIB_ARCADE.c_str(), LIB_ARCADE.size()))
				files.push_back(path + "/" + de->d_name);
			de = readdir(directory);
		}
		closedir(directory);
	}
	return files;
}

void ar::Core::loadGamesLib(std::vector<std::string> const &paths)
{
	for (auto &it: paths) {
		auto dl = new ar::DLoader(it);
		_gamesDL.push_back(dl);
		_highScores.push_back({0, "UNKNOWN", 0});
		_scores.push_back({0, "", 0});
		_games.push_back(((createGame *)dl->sym("createGame"))());
	}
}

void ar::Core::loadGraphicalsLib(std::vector<std::string> const &paths)
{
	for (auto &it: paths) {
		_graphicalsDL.push_back(new ar::DLoader(it));
	}
}

std::vector<std::string> ar::Core::getGamesName()
{
	std::vector<std::string> names;

	for (auto &it: _gamesDL) {
		ar::IGame *tmp = ((createGame *) it->sym("createGame"))();
		names.push_back(tmp->getGameName());
		((destroyGame *) it->sym("destroyGame"))(tmp);
	}
	return names;
}

void ar::Core::destroyActualGame()
{
	if (_game) {
		((destroyGame *)_gamesDL[_gamesIdx]->sym("destroyGame"))(_game);
		_game = nullptr;
	}
}

void ar::Core::destroyActualGraphical()
{
	if (_graphical) {
		((destroyDisplay *)_graphicalsDL[_graphicalsIdx]->sym("destroyDisplay"))(_graphical);
		_graphical = nullptr;
	}
}

void ar::Core::loadSpritesAndColors()
{
	if (_graphical->canHandleSprites())
		_graphical->loadResources(_game->getSpritesPath(), _game->getSprites());
	else
		_graphical->loadResources(_game->getColors());
}

void ar::Core::changeGameLib(int idx)
{
	if (_game)
		_game->setPause();
	//destroyActualGame();
	_gamesIdx = idx;
	//_game = ((createGame *) _gamesDL[_gamesIdx]->sym("createGame"))();
	_game = _games[_gamesIdx];
	_game->setPause();
	loadSpritesAndColors();
}

void ar::Core::changeGraphicalLib(int idx)
{
	destroyActualGraphical();
	_graphicalsIdx = idx;
	_graphical = ((createDisplay *) _graphicalsDL[_graphicalsIdx]->sym("createDisplay"))();
	if (_game)
		loadSpritesAndColors();
	if (_menu) {
		_graphical->initMenu(_gamesName, MENU_NAME, _graphicalsName);
	}
}

void ar::Core::refreshUserInterface()
{
	int score = _game->refreshScore();

	_scores[_gamesIdx].score = score;
	_scores[_gamesIdx].time = _game->refreshTimer();
	_scores[_gamesIdx].username = _username;
}

void ar::Core::nextGameLib()
{
	int idx = _gamesIdx + 1;
	if (idx >= (int) _gamesDL.size())
		idx = 0;
	changeGameLib(idx);
}

void ar::Core::prevGameLib()
{
	int idx = _gamesIdx - 1;
	if (idx < 0)
		idx = (int) _gamesDL.size() - 1;
	changeGameLib(idx);
}

void ar::Core::nextGraphicalLib()
{
	int idx = _graphicalsIdx + 1;
	if (idx >= (int) _graphicalsDL.size())
		idx = 0;
	changeGraphicalLib(idx);
}

void ar::Core::prevGraphicalLib()
{
	int idx = _graphicalsIdx - 1;
	if (idx < 0)
		idx = (int) _graphicalsDL.size() - 1;
	changeGraphicalLib(idx);
}

void ar::Core::activateMenu()
{
	//destroyActualGame();
	_game = nullptr;
	_graphical->initMenu(_gamesName, MENU_NAME, _graphicalsName);
	_menu = true;
}

void ar::Core::exit()
{
	destroyActualGame();
	destroyActualGraphical();
	_ended = true;
}

void ar::Core::restart()
{
	changeGameLib(_gamesIdx);
}

void ar::Core::manageGame(ar::Event &event)
{
	_game->manageKey(event);
	refreshUserInterface();
	if (_game->isGameOver()) {
		refreshUserInterface();
		if (_scores[_gamesIdx].score > _highScores[_gamesIdx].score)
			_highScores[_gamesIdx] = _scores[_gamesIdx];
		_scores[_gamesIdx] = {0, _username, 0};
		delete _games[_gamesIdx];
		_game = nullptr;
		_games[_gamesIdx] = (((createGame *)_gamesDL[_gamesIdx]->sym("createGame"))());
		//destroyActualGame();
		_graphical->initMenu(_gamesName, MENU_NAME, _graphicalsName);
		_menu = true;
	} else {
		_game->loop();
		_graphical->displayGame(_scores[_gamesIdx], _game->getMap());
	}
}

void ar::Core::manageMenu(ar::Event &event, int key)
{
	_graphical->refreshUsername(_username, key);
	_gamesIdx = _graphical->refreshMenu(event, _highScores);
	if ((unsigned int) _gamesIdx > _gamesDL.size() - 1)
		_gamesIdx = 0;
	if (event == ar::Event::AR_VALIDATE && (unsigned int)_gamesIdx < _gamesDL.size()) {
		_menu = false;
		_graphical->destroyMenu();
		changeGameLib(_gamesIdx);
	}
}

void ar::Core::start(std::string const &defaultPath)

{
	auto tmp = new ar::DLoader(defaultPath);
	_graphical = ((createDisplay *) tmp->sym("createDisplay"))();

	if (!_graphical)
		throw std::invalid_argument("Invalid argument: argument is not a valid graphical lib.");
	_gamesName = getGamesName();
	_graphicalsName = getAllFileOfDirWithPath(GRAPHICALS_PATH);
	_graphical->initMenu(_gamesName, MENU_NAME, _graphicalsName);
	while (!_ended) {
		int key;
		ar::Event event = _graphical->getEvent(key);

		if (_menu) {
			manageMenu(event, key);
		} else {
			manageGame(event);
		}
		if (_actions.find(event) != _actions.end())
			(this->*(_actions.find(event)->second))();
	}
}
