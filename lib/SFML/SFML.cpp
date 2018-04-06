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
	_window = new sf::RenderWindow(sf::VideoMode(_windowWidth, _windowHeight), "");
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
		if (sfEvent.key.shift && sfEvent.key.code == sf::Keyboard::Num1)
			return ar::Event::AR_PREV_GAME;
		if (sfEvent.key.shift && sfEvent.key.code == sf::Keyboard::Num2)
			return ar::Event::AR_NEXT_GAME;
		if (sfEvent.key.shift && sfEvent.key.code == sf::Keyboard::Num3)
			return ar::Event::AR_PREV_GRAPH_LIB;
		if (sfEvent.key.shift && sfEvent.key.code == sf::Keyboard::Num4)
			return ar::Event::AR_NEXT_GRAPH_LIB;
		if (sfEvent.key.code == sf::Keyboard::M)
			return ar::Event::AR_MENU;
		if (sfEvent.key.code == sf::Keyboard::P)
			return ar::Event::AR_PAUSE;
		if (sfEvent.key.code == sf::Keyboard::Space)
			return ar::Event::AR_ACTION;
		if (sfEvent.key.code == sf::Keyboard::Up)
			return ar::Event::AR_UP;
		if (sfEvent.key.code == sf::Keyboard::Right)
			return ar::Event::AR_RIGHT;
		if (sfEvent.key.code == sf::Keyboard::Left)
			return ar::Event::AR_LEFT;
		if (sfEvent.key.code == sf::Keyboard::Down)
			return ar::Event::AR_DOWN;
		if (sfEvent.key.code == sf::Keyboard::Escape)
			return ar::Event::AR_EXIT;
		if (sfEvent.key.code == sf::Keyboard::Return)
			return ar::Event::AR_VALIDATE;
		if (sfEvent.key.code == sf::Keyboard::R)
			return ar::Event::AR_RESTART;
	}
	return ar::Event::AR_UNKNOWN;
}

bool ar::SFML::canHandleSprites()
{
	return true;
}

void ar::SFML::displayGame(const ar::userInterface &UI, ar::Map &map)
{
	// TODO Sahel
	int dy = _windowHeight - 40 - 20;
	int dx = _windowWidth - 20 - 20;

	int sizeX = map.getWidth() ? dx / map.getWidth() : 0;
	int sizeY = map.getHeight() ? dy / map.getHeight() : 0;

	sf::RectangleShape def = _sprites[2];
	def.setSize(sf::Vector2f(sizeX, sizeY));

	std::cout << "delta: " << dx << "; " << dy << std::endl;
	std::cout << "size: " << sizeX << "; " << sizeY << std::endl;

	for (int y = 0; y < map.getHeight(); y++) {
		for (int x = 0; x < map.getWidth(); x++) {
			def.setPosition(x * sizeX + 20, y * sizeY + 40);
			_window->draw(def);
			_sprites[map[y][x]].setPosition(x * sizeX + 20, y * sizeY + 40);
			_sprites[map[y][x]].setSize(sf::Vector2f(sizeX, sizeY));
			_window->draw(_sprites[map[y][x]]);
		}
	}
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
}

int ar::SFML::refreshMenu(const ar::Event &key,
	const std::vector<ar::userInterface> &dataArray
)
{
	if (key == ar::Event::AR_UP && _idx > 1)
		_idx--;
	if (key == ar::Event::AR_DOWN && _idx < dataArray.size() -1)
		_idx++;


	// TODO Sahel Display
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