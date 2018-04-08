/*
** EPITECH PROJECT, 2018
** cpp_arcade
** File description:
** Created by martin.januario@epitech.eu,
*/

#include <sstream>
#include <iostream>
#include <cmath>
#include "SDL2.hpp"

ar::SDL2::SDL2()
{
	SDL_Init(SDL_INIT_VIDEO);
	IMG_Init(IMG_INIT_JPG | IMG_INIT_PNG);
	TTF_Init();

	_window = SDL_CreateWindow(
		"Un seul etre vous manque et tout est depeuple - SDL2",
		SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, _windowWidth,
		_windowHeight, SDL_WINDOW_RESIZABLE);
	_renderer = SDL_CreateRenderer(_window, -1,
		SDL_RENDERER_TARGETTEXTURE | SDL_RENDERER_PRESENTVSYNC);
	_font = TTF_OpenFont("./resources/arial.ttf", 10);
	if (!_window || !_renderer || !_font) {
		std::cerr << "Can't create window with SDL2" << std::endl;
		throw std::runtime_error("Can't create window with SDL2");
	}
	SDL_Surface *tmp;
	SDL_Surface *tmpBis;

	tmp = IMG_Load(
		"./resources/un_seul_etre_vous_manque_et_tout_est_depeuple_SDL2_background.jpg");
	tmpBis = IMG_Load(
		"./resources/un_seul_etre_vous_manque_et_tout_est_depeuple_SDL2_frame.png");
	if (!tmp || !tmpBis) {
		std::cerr << "Can't load asset file" << std::endl;
		throw std::runtime_error("Can't load asset file");
	}
	_menuBackground = SDL_CreateTextureFromSurface(_renderer, tmp);
	_frame = SDL_CreateTextureFromSurface(_renderer, tmpBis);
}

ar::SDL2::~SDL2()
{
	TTF_CloseFont(_font);
	SDL_DestroyTexture(_menuBackground);
	SDL_DestroyTexture(_frame);
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
		if ((realEvent == SDLK_4 || realEvent == SDLK_QUOTE) &&
			event.key.keysym.mod == KMOD_LSHIFT)
			return ar::Event::AR_NEXT_GRAPH_LIB;
		if ((realEvent == SDLK_3 || realEvent == SDLK_QUOTEDBL) &&
			event.key.keysym.mod == KMOD_LSHIFT)
			return ar::Event::AR_PREV_GRAPH_LIB;
		if ((realEvent == SDLK_2 || realEvent == 233) &&
			event.key.keysym.mod == KMOD_LSHIFT)
			return ar::Event::AR_NEXT_GAME;
		if ((realEvent == SDLK_1 || realEvent == '&') &&
			event.key.keysym.mod == KMOD_LSHIFT)
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
	int width = 0;
	int height = 0;
	SDL_GetWindowSize(_window, &width, &height);

	SDL_Rect defaultRect = {_sprites[2].x, _sprites[2].y, _sprites[2].width,
		_sprites[2].height};
	SDL_RenderClear(_renderer);
	for (int y = 0; y < map.getHeight(); ++y) {
		for (int x = 0; x < map.getWidth(); ++x) {
			SDL_Rect srcRect = {_sprites[map[y][x]].x,
				_sprites[map[y][x]].y,
				_sprites[map[y][x]].width,
				_sprites[map[y][x]].height};
			SDL_Rect dstRect = {
				(int)((float)x * (width / map.getWidth())),
				(y * (height / map.getHeight())),
				(int)std::ceil(
					(float)width / (float)map.getWidth()),
				(int)std::ceil((float)height /
					(float)map.getHeight())};
			SDL_RenderCopy(_renderer, _texture, &defaultRect,
				&dstRect);
			SDL_RenderCopy(_renderer, _texture, &srcRect, &dstRect);
		}
	}
	printHeaderUserInterface(UI);
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
	_sprites = sprites;
	SDL_FreeSurface(tmp);
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

void ar::SDL2::printStringMenu(SDL_Rect *dest, const char *str)
{
	SDL_Color color = {0, 255, 255, 255};
	SDL_Surface *surfaceMessage;
	SDL_Texture *message;
	SDL_Rect tmp = {dest->x, dest->y, dest->w, 40};
	char buffer[1];

	for (int i = 0; str && str[i] && tmp.x < tmp.x + tmp.w; ++i) {
		buffer[0] = str[i];
		surfaceMessage = TTF_RenderText_Solid(_font, buffer, color);
		message = SDL_CreateTextureFromSurface(_renderer,
			surfaceMessage);

		if (strlen(str)) {
			tmp.w = (dest->w / (int)strlen(str));
			tmp.w = (tmp.w > 20) ? 20 : tmp.w;
			tmp.x = dest->x + tmp.w * i;
		}

		SDL_RenderCopy(_renderer, message, NULL, &tmp);
		SDL_DestroyTexture(message);
	}
}

void ar::SDL2::printHeaderUserInterface(const ar::userInterface &UI, bool opt)
{
	int width = 0;
	int height = 0;
	SDL_GetWindowSize(_window, &width, &height);
	SDL_Rect texture_dest = {40, 0, width / 2 - 60, height / 20};;
	if (width <= 80)
		return;

	std::stringstream s;
	for (int x = 0; x < 3; ++x) {
		if (x == 0)
			s << "Best player: "
				<< ((UI.username.empty()) ? "Unknown" :
					UI.username);
		else if (x == 1)
			s << "Score: " << UI.score;
		else
			s << "Time: " << UI.time << "s";
		printStringMenu(&texture_dest, s.str().c_str());
		texture_dest = {40 + width / 2 + (width / 4) * x, 0,
			width / 4 - 40, height / 20};
		s.str("");
	}
	if (opt) {
		s << ((_username.empty()) ? "Unknown" : _username);
		texture_dest = {40, height / 20, width / 2 - 40,
			height / 30 * 2};
		printStringMenu(&texture_dest, "Current username: ");
		texture_dest = {width / 2 + 40, height / 20, width / 2 - 40,
			height / 30 * 2};
		printStringMenu(&texture_dest, s.str().c_str());
	}
}

void ar::SDL2::printGraphicalList(void)
{
	int width = 0;
	int height = 0;
	SDL_GetWindowSize(_window, &width, &height);
	std::stringstream s;

	SDL_Rect texture_dest = {width / 2 + width / 4, height / 20 * 2, width / 4, height - (height / 20) * 2};
	SDL_RenderCopy(_renderer, _frame, NULL, &texture_dest);

	texture_dest.x += (width / 2) / 13;
	texture_dest.w -= (width / 2) / 9;

	for (auto it = _graphicalName.begin(); it != _graphicalName.end() ; ++it) {
		s.str("");
		s << (*it).substr((*it).find_last_of('/') + 1);


		printStringMenu(&texture_dest, s.str().c_str());
		texture_dest.y += ((height - (height / 20) * 2) + 20) / (_graphicalName.size() + 1);
	}
}

void ar::SDL2::printGameList(void)
{
	int width = 0;
	int height = 0;
	SDL_GetWindowSize(_window, &width, &height);
	std::stringstream s;

	SDL_Rect texture_dest = {width / 2, height / 20 * 2, width / 4, height - (height / 20) * 2};
	SDL_RenderCopy(_renderer, _frame, NULL, &texture_dest);

	texture_dest.x += (width / 2) / 13;
	texture_dest.w -= (width / 2) / 9;

	unsigned int cmp = 0;
	for (auto it = _gameName.begin(); it != _gameName.end() ; ++it) {
		s.str("");
		s << (*it).substr((*it).find_last_of('/') + 1);

		if (cmp == _index)
			TTF_SetFontStyle(_font, TTF_STYLE_UNDERLINE);


		printStringMenu(&texture_dest, s.str().c_str());
		texture_dest.y += ((height - (height / 20) * 2) + 20) / (_gameName.size() + 1);
		TTF_SetFontStyle(_font, TTF_STYLE_NORMAL);
		cmp++;
	}
}

int ar::SDL2::refreshMenu(const ar::Event &key,
	const std::vector<ar::userInterface> &dataArray
)
{
	int width = 0;
	int height = 0;
	SDL_GetWindowSize(_window, &width, &height);

	SDL_Rect texture_dest = {0, 0, width, height};
	SDL_RenderClear(_renderer);

	if (key == ar::Event::AR_UP && _index > 0)
		_index--;
	if (key == ar::Event::AR_DOWN && _index < dataArray.size() - 1)
		_index++;

	SDL_RenderCopy(_renderer, _menuBackground, NULL, &texture_dest);
	printHeaderUserInterface(dataArray[_index], true);
	printGraphicalList();
	printGameList();
	SDL_RenderPresent(_renderer);
	return _index;
}

void ar::SDL2::refreshUsername(std::string &username, int realKey)
{
	if ((realKey >= 'a' && realKey <= 'z') ||
		(realKey >= 'A' && realKey <= 'Z'))
		username += (char)realKey;
	if (realKey == 8 && !username.empty())
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