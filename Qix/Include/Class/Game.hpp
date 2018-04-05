/*
** EPITECH PROJECT, 2018
** cpp_arcade
** File description:
** Created by martin.januario@epitech.eu,
*/

#ifndef CPP_ARCADE_GAME_HPP
# define CPP_ARCADE_GAME_HPP

# include <map>
# include "ManageMap.hpp"
# include "Arcade.hpp"
# include "IGame.hpp"

namespace ar {

	class Qix : public IGame {
		public:
		Qix();

		void manageKey(const Event &key);

		void loop();
		void setPause();
		bool isGameOver();

		int refreshScore() override;
		int refreshTimer() override;

		const std::string getGameName() const override;
		Map &getMap() override;
		const std::map<unsigned char, spriteCoords> &getSprites() const override; //dans games, à l'initialisation
		const std::string getSpritesPath() const override;
		const std::map<unsigned char, colorVector> &getColors() const override; //dans games, à l'initialisation

		ManageMap _manageMap;
		protected:

		private:
		userInterface _data;
		std::map<unsigned char, spriteCoords> _sprites;
		std::string _spritePath;
		std::map<unsigned char, colorVector> _colors;
	};
}
#endif //CPP_ARCADE_GAME_HPP
