//
// EPITECH PROJECT, 2018
// Arcade
// File description:
// Snake class
//

#ifndef		SNAKE_HPP_
#define		SNAKE_HPP_

#include	<map>
#include	<vector>
#include	"Arcade.hpp"
#include	"IGame.hpp"
#include	"Map.hpp"

enum		Direction {
	UP,
	DOWN,
	LEFT,
	RIGHT
};

enum		Tile {
	BLACK,
	WHITE,
	DEFAULT,
	WALL,
	EMPTY,
	OPEN_MOUTH_UP,
	OPEN_MOUTH_LEFT,
	OPEN_MOUTH_RIGHT,
	OPEN_MOUTH_DOWN,
	CLOSED_MOUTH_UP,
	CLOSED_MOUTH_LEFT,
	CLOSED_MOUTH_RIGHT,
	CLOSED_MOUTH_DOWN,
	EMPTY_BODY_UP,
	EMPTY_BODY_LEFT,
	EMPTY_BODY_RIGHT,
	EMPTY_BODY_DOWN,
	FULL_BODY_UP,
	FULL_BODY_LEFT,
	FULL_BODY_RIGHT,
	FULL_BODY_DOWN,
	EMPTY_CORNER_RIGHT_TO_UP,
	EMPTY_CORNER_LEFT_TO_UP,
	EMPTY_CORNER_UP_TO_LEFT,
	EMPTY_CORNER_DOWN_TO_LEFT,
	EMPTY_CORNER_UP_TO_RIGHT,
	EMPTY_CORNER_DOWN_TO_RIGHT,
	EMPTY_CORNER_RIGHT_TO_DOWN,
	EMPTY_CORNER_LEFT_TO_DOWN,
	FULL_CORNER_RIGHT_TO_UP,
	FULL_CORNER_LEFT_TO_UP,
	FULL_CORNER_UP_TO_LEFT,
	FULL_CORNER_DOWN_TO_LEFT,
	FULL_CORNER_UP_TO_RIGHT,
	FULL_CORNER_DOWN_TO_RIGHT,
	FULL_CORNER_RIGHT_TO_DOWN,
	FULL_CORNER_LEFT_TO_DOWN,
	TAIL_UP,
	TAIL_LEFT,
	TAIL_RIGHT,
	TAIL_DOWN,
	PELLET
};

class		Snake : public ar::IGame
{
public:
	Snake();
	~Snake();

	void manageKey(const ar::Event &Key);
	const std::map<unsigned char, ar::spriteCoords> &getSprites() const;
	const std::string getSpritesPath() const;
	const std::map<unsigned char, ar::colorVector> &getColors() const;
	int refreshScore();
	int refreshTimer();
	bool isGameOver();
	ar::Map &getMap();
	void loop();
	const std::string getGameName() const;
	void setPause();

private:

	struct		SnakePart {
		std::size_t	row;
		std::size_t	col;
		bool		full;
	};

	SnakePart createSnakePart(std::size_t row, std::size_t col, bool full);
	void addPellet();
	void updateHead();
	void straightLine();
	void cornerToTopRight();
	void cornerToBottomRight();
	void cornerFromLeftToRight();
	void cornerToTopLeft();
	void cornerToBottomLeft();
	void cornerFromRightToLeft();
	void corner();
	void updateFirstBodyPart();
	void updateTail(Tile tail);
	void updateSnake(Tile tile, std::size_t row, std::size_t col);
	bool possibleDestination(Tile tile);
	void goUp();
	void goDown();
	void goLeft();
	void goRight();
	void initiateGame();
	void updateMap();

	Direction _direction;
	bool _pause;
	bool _classicMode;
	int _score;
	int _timer;
	int _time;
	bool _gameOver;
	ar::Map _map;
	const std::size_t _height;
	const std::size_t _width;
	std::vector<SnakePart> _snake;
	std::vector<std::vector<Tile> > _movementMap;
};

#endif		/* !SNAKE_HPP_ */
