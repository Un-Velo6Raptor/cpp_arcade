/*
** EPITECH PROJECT, 2021
** arcade
** File description:
** game interface
*/

#ifndef CPP_ARCADE_IGAME_HPP
# define CPP_ARCADE_IGAME_HPP

#include <map>
#include "Arcade.hpp"
#include "Map.hpp"

namespace ar {
	class IGame {
	public:
		IGame() = default;
		virtual ~IGame() = default;

		virtual void manageKey(const Event &key) = 0;
		virtual const std::map<unsigned char, spriteCoords> &getSprites() const = 0;
		virtual const std::string getSpritesPath() const = 0;
		virtual const std::map<unsigned char, colorVector> &getColors() const = 0;
		virtual int refreshScore() = 0;
		virtual int refreshTimer() = 0;
		virtual bool isGameOver() = 0;
		virtual Map &getMap() = 0;
		virtual void loop() = 0;
		virtual const std::string getGameName() const = 0;
		virtual void setPause() = 0;
	};

	typedef ar::IGame *createGame();
	typedef void destroyGame(ar::IGame *);
};

#endif //CPP_ARCADE_IGAME_HPP
