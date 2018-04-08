/*
** EPITECH PROJECT, 2018
** cpp_arcade
** File description:
** Created by martin.januario@epitech.eu,
*/

#include <iostream>
#include "SDL2.hpp"

ar::SDL2::SDL2()
{
	SDL_Init(SDL_INIT_VIDEO);
	IMG_Init(IMG_INIT_JPG | IMG_INIT_PNG);
	TTF_Init();

	_window = SDL_CreateWindow(_menuName.c_str(),
		SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, _windowWidth,
		_windowHeight, SDL_WINDOW_OPENGL);
	_renderer = SDL_CreateRenderer(_window, -1,
		SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);


	SDL_SetWindowResizable(_window, SDL_TRUE);
}

ar::SDL2::~SDL2()
{
	SDL_DestroyWindow(_window);
	SDL_DestroyRenderer(_renderer);
	TTF_Quit();
	IMG_Quit();
	SDL_Quit();
}

bool ar::SDL2::canHandleSprites()
{
	return true;
}

ar::Event ar::SDL2::getEvent(int &realEvent)
{
	SDL_Event event;

	realEvent = -1;
	if (!SDL_PollEvent(&event))
		return ar::Event::AR_UNKNOWN;
	if (event.type == SDL_QUIT)
		return ar::Event::AR_EXIT;
	if (event.type == SDL_WINDOWEVENT_RESIZED)
		return ar::Event::AR_RESIZE;
	if (event.type == SDL_KEYDOWN) {
		realEvent = event.key.keysym.sym;
		if ((realEvent == SDLK_4 || realEvent == SDLK_QUOTE) && event.key.keysym.mod == KMOD_LSHIFT)
			return ar::Event::AR_NEXT_GRAPH_LIB;
		if ((realEvent == SDLK_3 || realEvent == SDLK_QUOTEDBL) && event.key.keysym.mod == KMOD_LSHIFT)
			return ar::Event::AR_PREV_GRAPH_LIB;
		if ((realEvent == SDLK_2) && event.key.keysym.mod == KMOD_LSHIFT) // TODO Martin, ne pas oublier
			return ar::Event::AR_NEXT_GAME;
		if ((realEvent == SDLK_1 || realEvent == SDLK_AMPERSAND) && event.key.keysym.mod == KMOD_LSHIFT)
			return ar::Event::AR_PREV_GAME;
		if (realEvent == SDLK_m)
			return ar::Event::AR_MENU;
		if (realEvent == SDLK_p)
			return ar::Event::AR_PAUSE;
		if (realEvent == SDLK_r)
			return ar::Event::AR_RESTART;
		if (realEvent == SDLK_SPACE)
			return ar::Event::AR_ACTION;
		if (realEvent == SDLK_UP)
			return ar::Event::AR_UP;
		if (realEvent == SDLK_DOWN)
			return ar::Event::AR_DOWN;
		if (realEvent == SDLK_LEFT)
			return ar::Event::AR_LEFT;
		if (realEvent == SDLK_RIGHT)
			return ar::Event::AR_RIGHT;
		if (realEvent == SDLK_ESCAPE)
			return ar::Event::AR_EXIT;
		if (realEvent == SDLK_RETURN)
			return ar::Event::AR_VALIDATE;
	}
	return ar::Event::AR_UNKNOWN;
}

void ar::SDL2::displayGame(const ar::userInterface &UI, ar::Map &map)
{
	SDL_Rect rect = {0, 0, 0, 0};
	int width = 0;
	int height = 0;
	SDL_GetWindowSize(_window, &width, &height);

	for (int y = 0; map[y] ; ++y) {
		for (int x = 0; x < map.getWidth(); ++x) {
			rect = {y*width/map.getWidth(), x*height/map.getHeight(), width / map.getWidth(), height / map.getHeight()};
			SDL_RenderCopy(_renderer, _texture, &rect, NULL);
		}
	}
	SDL_RenderPresent(_renderer);
}

void ar::SDL2::loadResources(
	const std::map<unsigned char, ar::colorVector> &color
)
{
	(void)color;
}

void ar::SDL2::loadResources(const std::string &filePath,
	const std::map<unsigned char, ar::spriteCoords> &sprites
)
{
	SDL_Surface *tmp;

	tmp = IMG_Load(filePath.c_str());
	if (!tmp) {
		std::cerr << "Can't load asset file" << std::endl;
		throw std::runtime_error("Can't load asset file");
	}
	_texture = SDL_CreateTextureFromSurface(_renderer, tmp);
	SDL_SetTextureBlendMode(_texture, SDL_BLENDMODE_BLEND);
	_sprites = sprites;
}

void ar::SDL2::initMenu(const std::vector<std::string> &menuChoices,
	const std::string &menuName, const std::vector<std::string> &display
)
{
	SDL_RenderClear(_renderer);
	_gameName = menuChoices;
	_graphicalName = display;
	_menuName = menuName;
}

int ar::SDL2::refreshMenu(const ar::Event &key,
	const std::vector<ar::userInterface> &dataArray
)
{
	SDL_RenderClear(_renderer);
	if (key == ar::Event::AR_UP && _index > 0)
		_index--;
	if (key == ar::Event::AR_DOWN && _index < dataArray.size() - 1)
		_index++;

	// Todo Martin display
}

void ar::SDL2::refreshUsername(std::string &username, int realKey)
{
	if ((realKey >= 'a' && realKey <= 'z') ||
		(realKey >= 'A' && realKey <= 'Z'))
		username += (char)realKey;
	if (realKey == SDLK_DELETE && !username.empty())
		username.pop_back();
	_username = username;
}

void ar::SDL2::destroyMenu()
{
	SDL_RenderClear(_renderer);
	_index = 0;
	_menuName.clear();
	_graphicalName.clear();
	_gameName.clear();
}

extern "C" ar::IDisplay *createDisplay()
{
	return new ar::SDL2();
}

extern "C" void destroyDisplay(ar::SDL2 *other)
{
	delete other;
}