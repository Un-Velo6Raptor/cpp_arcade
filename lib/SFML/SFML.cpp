/*
** EPITECH PROJECT, 2021
** cpp_arcade
** File description:
** Created by sahel.lucas-saoudi@epitech.eu,
*/

#include <iostream>
#include <zconf.h>
#include "SFML.hpp"

ar::SFML::SFML()
{
	_window = new sf::RenderWindow(sf::VideoMode(_windowWidth, _windowHeight), "Un seul etre vous manque est tout est depeuple - SFML");
	if (!_font.loadFromFile(_fontPath)) {
		std::cerr << "Can't load font (" << _fontPath << ") for SFML" << std::endl;
		throw std::runtime_error("Can't load font (" + _fontPath + ") for SFML");
	}

	if (!_menuBackground.loadFromFile(_backgroundPath)) {
		std::cerr << "Can't load Manu background (" << _backgroundPath << ") for SFML" << std::endl;
		throw std::runtime_error("Can't load Menu background");
	}

	if (!_titleFont.loadFromFile(_titleFontPath)) {
		std::cerr << "Can't load Title font" << std::endl;
		throw std::runtime_error("Can't load Title font");
	}

	_windowHeight = _window->getSize().y;
	_windowWidth = _window->getSize().x;
}

ar::SFML::~SFML() {
	delete _window;
}

ar::Event ar::SFML::getEvent(int &realEvent)
{
	sf::Event sfEvent = sf::Event();

	if (!_window->pollEvent(sfEvent))
		return ar::Event::AR_UNKNOWN;
	realEvent = -1;
	if (sfEvent.type == sf::Event::Closed)
		return ar::Event::AR_EXIT;
	if (sfEvent.type == sf::Event::Resized)
		return ar::Event::AR_RESIZE;
	if (sfEvent.type == sf::Event::KeyPressed) {
		realEvent = sfEvent.key.code;
		if (_events.find({sfEvent.key.shift, sfEvent.key.code}) != _events.end())
			return _events[{sfEvent.key.shift, sfEvent.key.code}];
	}
	return ar::Event::AR_UNKNOWN;
}

bool ar::SFML::canHandleSprites()
{
	return true;
}

void ar::SFML::displayScore(int score, int boxSizeX, int boxSizeY)
{
	sf::Text titleHighScore("Score", _font, _fontSize);
	titleHighScore.setPosition(_userMarginLeft + boxSizeX, _userMarginTop);

	sf::Text highScore(std::to_string(score), _font, _fontSize);
	highScore.setPosition(_userMarginLeft + boxSizeX, _userMarginTop + boxSizeY + 20);

	_window->draw(titleHighScore);
	_window->draw(highScore);
}

void ar::SFML::displayTime(int timer, int boxSizeX, int boxSizeY)
{
	sf::Text titleTime("Time", _font, _fontSize);
	titleTime.setPosition(_userMarginLeft + boxSizeX * 2, _userMarginTop);

	sf::Text time(std::to_string(timer), _font, _fontSize);
	time.setPosition(_userMarginLeft + boxSizeX * 2, _userMarginTop + boxSizeY + 20);

	_window->draw(titleTime);
	_window->draw(time);
}

void ar::SFML::displayUsername(std::string const &user, int boxSizeX,
	int boxSizeY
)
{
	sf::Text titleUsername("Username", _font, _fontSize);
	titleUsername.setPosition(_userMarginLeft, _userMarginTop);

	sf::Text username(user, _font, _fontSize);
	username.setPosition(_userMarginLeft, _userMarginTop + boxSizeY + 20);

	_window->draw(titleUsername);
	_window->draw(username);
}

void ar::SFML::displayUserInterface(ar::userInterface const &user)
{
	int dx = _windowWidth - _userMarginLeft - _userMarginRight;
	int dy = _userHeight - _userMarginTop - _userMarginBottom;

	int boxSizeX = dx / 3;
	int boxSizeY = dy / 2;

	displayUsername(user.username, boxSizeX, boxSizeY);
	displayScore(user.score, boxSizeX, boxSizeY);
	displayTime(user.time, boxSizeX, boxSizeY);
}

void ar::SFML::displayGame(const ar::userInterface &UI, ar::Map &map)
{
	_window->clear(sf::Color::Black);

	int dy = _windowHeight - _gameMarginTop - _gameMarginBottom;
	int dx = _windowWidth - _gameMarginRight - _gameMarginLeft;

	int sizeX = map.getWidth() ? dx / (map.getWidth()) : 0;
	int sizeY = map.getHeight() ? dy / (map.getHeight()) : 0;

	sf::RectangleShape def = _sprites[2];
	def.setSize(sf::Vector2f(sizeX, sizeY));

	for (int y = 0; y < map.getHeight(); y++) {
		for (int x = 0; x < map.getWidth(); x++) {
			int realX = x * sizeX + _gameMarginLeft;
			int realY = y * sizeY + _gameMarginTop;

			def.setPosition(realX, realY);
			_window->draw(def);
			_sprites[map[y][x]].setPosition(realX, realY);
			_sprites[map[y][x]].setSize(sf::Vector2f(sizeX, sizeY));
			_window->draw(_sprites[map[y][x]]);
		}
	}
	displayUserInterface(UI);
	_window->display();
}

void ar::SFML::loadResources(
	const std::map<unsigned char, ar::colorVector> &colors
)
{
	(void) colors;
}

void ar::SFML::loadResources(const std::string &filePath,
	const std::map<unsigned char, ar::spriteCoords> &sprites
)
{
	if (!_texture.loadFromFile(filePath)) {
		std::cerr << "Can't load Assets file" << std::endl;
		throw std::invalid_argument("Assets file not found");
	}
	for (auto &it: sprites) {
		_sprites[it.first] = sf::RectangleShape();
		_sprites[it.first].setTexture(&_texture);
		_sprites[it.first].setTextureRect( sf::Rect<int>(it.second.x, it.second.y, it.second.width, it.second.height));
	}
}

void ar::SFML::initMenu(const std::vector<std::string> &menuChoices,
	const std::string &menuName, const std::vector<std::string> &display
)
{
	_window->clear(sf::Color::Black);
	_menuName = menuName;
	_menuGamesName = menuChoices;
	_menuGraphicalsLib = display;
}

void ar::SFML::refreshUsername(std::string &name, int realKey)
{
	if (realKey >= sf::Keyboard::A && realKey <= sf::Keyboard::Z)
		name += (char) realKey + 'a';
	if (realKey == sf::Keyboard::BackSpace && !name.empty())
		name.pop_back();
	_username = name;
}

void ar::SFML::menuDisplayGames()
{
	for (int i = 0; i < (int)_menuGamesName.size(); i++) {
		sf::Color color = sf::Color::White;
		if (i == _idx)
			color = sf::Color::Red;
		unsigned int size = _windowHeight / 2 / _menuGamesName.size();
		sf::Text game(_menuGamesName[i], _titleFont, size > 40 ? 40 : size);
		game.setPosition(_windowWidth / 2, _windowHeight / 2.0f + (_windowHeight / 2.0f / _menuGamesName.size()) * i);
		game.setFillColor(color);
		_window->draw(game);
	}
}

void ar::SFML::menuDisplayGraphicals()
{
	for (int i = 0; i < (int)_menuGraphicalsLib.size(); i++) {
		std::string libName = _menuGraphicalsLib[i];

		sf::Text lib(libName.substr(libName.find_last_of('/') + 1), _titleFont, 12);
		lib.setPosition(1, _userHeight + _userMarginBottom + _userMarginTop + 15 * i);
		_window->draw(lib);
	}
}

void ar::SFML::menuDisplayUsername()
{
	sf::Text titleUsername("Username = " + _username, _font, 40);
	titleUsername.setPosition(_windowWidth / 3.0f, 260);
	_window->draw(titleUsername);
}

void ar::SFML::menuDisplayTitle()
{
	sf::Text title(_menuName, _titleFont, 150);
	title.setFillColor(sf::Color::Cyan);
	title.setPosition(_windowWidth / 3.0f, 100);
	_window->draw(title);
}

void ar::SFML::menuManageKey(ar::Event const &key,
	std::vector<ar::userInterface> const &datas
)
{
	if (key == ar::Event::AR_UP && _idx > 0)
		_idx--;
	if (key == ar::Event::AR_DOWN && (unsigned int) _idx < datas.size() -1)
		_idx++;
	if ((unsigned int) _idx > datas.size() - 1)
		_idx = 0;
}

int ar::SFML::refreshMenu(const ar::Event &key,
	const std::vector<ar::userInterface> &dataArray
)
{
	_window->clear(sf::Color::Black);
	menuManageKey(key, dataArray);
	_window->draw(sf::Sprite(_menuBackground));

	menuDisplayTitle();
	menuDisplayUsername();
	menuDisplayGames();
	menuDisplayGraphicals();
	displayUserInterface(dataArray[_idx]);

	_window->display();
	return _idx;
}

void ar::SFML::destroyMenu()
{
	_window->clear(sf::Color::Black);
	_menuGamesName.clear();
	_menuGraphicalsLib.clear();
	_menuName.clear();
	_idx = 0;
}

extern "C" ar::IDisplay *createDisplay() {
	return new ar::SFML();
}

extern "C" void destroyDisplay(ar::SFML *sfml) {
	delete sfml;
}