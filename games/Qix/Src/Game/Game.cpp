/*
** EPITECH PROJECT, 2018
** cpp_arcade
** File description:
** Created by martin.januario@epitech.eu,
*/

#include "Game.hpp"

ar::Qix::Qix() : _manageMap(30, 30), _isPaused(true)
{
	std::srand(std::time(nullptr));

	this->_data = {0, "Unknown", 0};
	this->_spritePath = "./resources/un_seul_etre_vous_manque_et_tout_est_depeuple_qix.png";

	this->_startPause = -1;
	this->_tmpTimer = 0;
	this->_timer = std::time(nullptr);
	this->_time = clock();

	this->_life = 3;
	this->_patternQix = 0;
	this->_listSharks.emplace_back(this->_manageMap, true);
	this->_listSharks.emplace_back(this->_manageMap, false);
	this->_flame = nullptr;

	this->_lastBorderPosX = this->_manageMap._map.getPlayerX();
	this->_lastBorderPosY = this->_manageMap._map.getPlayerY();
	this->_actualDir = DirObj::UNKNOWN;
	this->_isPlayerStopped = false;

	this->_sprites.insert({0, {0, 0, 32, 32}});
	this->_sprites.insert({1, {0, 0, 32, 32}});
	this->_sprites.insert({2, {0, 0, 32, 32}});
	this->_sprites.insert({3, {32, 0, 32, 32}});
	this->_sprites.insert({4, {0, 32, 32, 32}});
	this->_sprites.insert({5, {64, 0, 32, 32}});
	this->_sprites.insert({6, {0, 64, 32, 32}});
	this->_sprites.insert({7, {32, 64, 32, 32}});
	this->_sprites.insert({8, {64, 64, 32, 32}});
	this->_sprites.insert({9, {32, 32, 32, 32}});
	this->_sprites.insert({10, {64, 32, 32, 32}});

	colorVector color = {0, 255, 255};
	this->_colors.insert({3, color});

	color = {255, 255, 255};
	this->_colors.insert({0, color});

	color = {0, 0, 0};
	this->_colors.insert({1, color});

	color = {0, 0, 0};
	this->_colors.insert({2, color});

	color = {0, 0, 0};
	this->_colors.insert({4, color});

	color = {255, 255, 0};
	this->_colors.insert({5, color});

	color = {255, 0, 0};
	this->_colors.insert({6, color});

	color = {0, 0, 0};
	this->_colors.insert({7, color});

	color = {255, 100, 100};
	this->_colors.insert({8, color});

	color = {0, 0, 255};
	this->_colors.insert({9, color});

	color = {255, 0, 255};
	this->_colors.insert({10, color});
}

ar::Qix::~Qix()
{
	if (this->_flame)
		delete this->_flame;
}

extern "C" ar::Qix *createGame() {
	return new ar::Qix;
}

extern "C" void destroyGame(ar::Qix *obj) {
	delete obj;
}
