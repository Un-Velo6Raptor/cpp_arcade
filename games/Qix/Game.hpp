/*
** EPITECH PROJECT, 2018
** cpp_arcade
** File description:
** Created by martin.januario@epitech.eu,
*/

#ifndef CPP_ARCADE_GAME_HPP
# define CPP_ARCADE_GAME_HPP

# include <cstdlib>
# include <ctime>
# include <time.h>
# include <map>
# include <vector>
# include "ManageMap.hpp"
# include "Sharks.hpp"
# include "Arcade.hpp"
# include "IGame.hpp"
# include "Enum.hpp"

namespace ar {

	class Qix : public IGame {
		public:
		Qix();
		~Qix();

		// ManageKeyGame
		void manageKey(const Event &key);

		// ManageGame
		void loop();
		void setPause();
		bool isGameOver();

		// GameRefresh
		int refreshScore() override;
		int refreshTimer() override;

		// GameGetter
		const std::string getGameName() const override;
		Map &getMap() override;
		const std::map<unsigned char, spriteCoords> &getSprites() const override; //dans games, à l'initialisation
		const std::string getSpritesPath() const override;
		const std::map<unsigned char, colorVector> &getColors() const override; //dans games, à l'initialisation
		std::size_t getLife() const;
		int getLastBorderPosX() const;
		int getLastBorderPosY() const;

		ManageMap _manageMap;
		protected:

		private:
		userInterface _data;
		std::map<unsigned char, spriteCoords> _sprites;
		std::string _spritePath;
		std::map<unsigned char, colorVector> _colors;

		bool _isPaused;
		int _life;
		std::size_t _patternQix;
		MapPattern _behindPlayer;

		int _lastBorderPosX;
		int _lastBorderPosY;
		bool _isPlayerStopped;
		DirObj _actualDir;

		std::vector<ManageSharks> _listSharks;
		ManageSharks *_flame;

		int _startPause;
		int _tmpTimer;
		int _timer;
		int _time;

		// init
		void initSprites(void);
		void initColor(void);

		// ManageGame
		void updateScore(void);
		void joinTheBorder(void);
		float percentOfMapCoverage(int sizeMob, int walkableArea);
		int **copyMapForUpdate(void);
		void startLoopListSharks(void);
		void FireOnTrailCheck(void);
		void checkStartFire(void);

		// ManageGameKey
		void KeyUpPressed(void);
		void KeyDownPressed(void);
		void KeyLeftPressed(void);
		void KeyRightPressed(void);
		void SetDirFlameToGo(void);

		// ManagePlayer
		int movePlayer(void);
		int ToLeft(int);
		int ToRight(int);
		int ToUp(int);
		int ToDown(int);
		int GetCharTo(int x, int y);

		// ManageSquare
		void fillBox(bool opt = false);
		int GoThroughTheMap(int x, int y);
		void resetSpecificCharMap(MapPattern);
		void updateMap(void);

		// ManagaeQix
		int randomMoveQix(void);
		int QixToLeft(void);
		int QixToRight(void);
		int QixToUp(void);
		int QixToDown(void);
	};
}

#endif //CPP_ARCADE_GAME_HPP
