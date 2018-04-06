//
// EPITECH PROJECT, 2018
// arcade
// File description:
// Snake Class
//

#include	<algorithm>
#include	<iostream>
#include	<time.h>
#include	<ctime>
#include	"Arcade.hpp"
#include	"Snake.hpp"

const std::map<unsigned char, ar::spriteCoords>	sprites {
	{ 0, ar::spriteCoords { 0, 0, 64, 64 } },	// BLACK
	{ 1, ar::spriteCoords { 64, 0, 64, 64 } },	// WHITE
	{ 2, ar::spriteCoords { 128, 0, 64, 64 } },	// DEFAULT
	{ 3, ar::spriteCoords { 192, 0, 64, 64 } },	// WALL
	{ 4, ar::spriteCoords { 256, 0, 64, 64 } },	// EMPTY
	{ 5, ar::spriteCoords { 320, 0, 64, 64 } },	// OPEN_MOUTH_UP
	{ 6, ar::spriteCoords { 384, 0, 64, 64 } },	// OPEN_MOUTH_LEFT
	{ 7, ar::spriteCoords { 0, 64, 64, 64 } },	// OPEN_MOUTH_RIGHT
	{ 8, ar::spriteCoords { 64, 64, 64, 64 } },	// OPEN_MOUTH_DOWN
	{ 9, ar::spriteCoords { 128, 64, 64, 64 } },	// CLOSED_MOUTH_UP
	{ 10, ar::spriteCoords { 192, 64, 64, 64 } },
	{ 11, ar::spriteCoords { 256, 64, 64, 64 } },
	{ 12, ar::spriteCoords { 320, 64, 64, 64 } },
	{ 13, ar::spriteCoords { 128, 128, 64, 64 } },	// EMPTY_BODY_UP
	{ 14, ar::spriteCoords { 0, 128, 64, 64 } },
	{ 15, ar::spriteCoords { 64, 128, 64, 64 } },
	{ 16, ar::spriteCoords { 384, 64, 64, 64 } },
	{ 17, ar::spriteCoords { 192, 128, 64, 64 } },	// FULL_BODY_UP
	{ 18, ar::spriteCoords { 192, 128, 64, 64 } },
	{ 19, ar::spriteCoords { 256, 128, 64, 64 } },
	{ 20, ar::spriteCoords { 256, 128, 64, 64 } },
	{ 21, ar::spriteCoords { 384, 128, 64, 64 } },	// EMPTY_CORNER_RIGHT_TO_UP
	{ 22, ar::spriteCoords { 0, 192, 64, 64 } },	// LEFT_TO_UP
	{ 23, ar::spriteCoords { 0, 192, 64, 64 } },	// UP_TO_LEFT
	{ 24, ar::spriteCoords { 64, 192, 64, 64 } },	// DOWN_TO_LEFT
	{ 25, ar::spriteCoords { 384, 128, 64, 64 } },	// UP_TO_RIGHT
	{ 26, ar::spriteCoords { 320, 128, 64, 64 } },	// DOWN_TO_RIGHT
	{ 27, ar::spriteCoords { 320, 128, 64, 64 } },	// RIGHT_TO_DOWN
	{ 28, ar::spriteCoords { 64, 192, 64, 64 } },	// LEFT_TO_DOWN
	{ 29, ar::spriteCoords { 256, 192, 64, 64 } },	// FULL_CORNER_RIGHT_TO_UP
	{ 30, ar::spriteCoords { 320, 192, 64, 64 } },
	{ 31, ar::spriteCoords { 320, 192, 64, 64 } },
	{ 32, ar::spriteCoords { 128, 192, 64, 64 } },
	{ 33, ar::spriteCoords { 256, 192, 64, 64 } },
	{ 34, ar::spriteCoords { 192, 192, 64, 64 } },
	{ 35, ar::spriteCoords { 192, 192, 64, 64 } },
	{ 36, ar::spriteCoords { 128, 192, 64, 64 } },
	{ 37, ar::spriteCoords { 384, 192, 64, 64 } },	// TAIL_UP
	{ 38, ar::spriteCoords { 0, 256, 64, 64 } },
	{ 39, ar::spriteCoords { 64, 256, 64, 64 } },
	{ 40, ar::spriteCoords { 128, 256, 64, 64 } },
	{ 41, ar::spriteCoords { 192, 256, 64, 64 } },	// PELLET
};

const std::map<unsigned char, ar::colorVector>	colors {
	{ 0, ar::colorVector { 0, 0, 0 } },
	{ 1, ar::colorVector { 255, 255, 255 } },
	{ 2, ar::colorVector { 255, 255, 255 } },
	{ 3, ar::colorVector { 0, 0, 0 } },
	{ 4, ar::colorVector { 255, 255, 255 } },
	{ 5, ar::colorVector { 255, 0, 0 } },
	{ 6, ar::colorVector { 255, 0, 0 } },
	{ 7, ar::colorVector { 255, 0, 0 } },
	{ 8, ar::colorVector { 255, 0, 0 } },
	{ 9, ar::colorVector { 255, 0, 0 } },
	{ 10, ar::colorVector { 255, 0, 0 } },
	{ 11, ar::colorVector { 255, 0, 0 } },
	{ 12, ar::colorVector { 255, 0, 0 } },
	{ 13, ar::colorVector { 0, 255, 0 } },
	{ 14, ar::colorVector { 0, 255, 0 } },
	{ 15, ar::colorVector { 0, 255, 0 } },
	{ 16, ar::colorVector { 0, 255, 0 } },
	{ 17, ar::colorVector { 0, 255, 0 } },
	{ 18, ar::colorVector { 0, 255, 0 } },
	{ 19, ar::colorVector { 0, 255, 0 } },
	{ 20, ar::colorVector { 0, 255, 0 } },
	{ 21, ar::colorVector { 0, 255, 0 } },
	{ 22, ar::colorVector { 0, 255, 0 } },
	{ 23, ar::colorVector { 0, 255, 0 } },
	{ 24, ar::colorVector { 0, 255, 0 } },
	{ 25, ar::colorVector { 0, 255, 0 } },
	{ 26, ar::colorVector { 0, 255, 0 } },
	{ 27, ar::colorVector { 0, 255, 0 } },
	{ 28, ar::colorVector { 0, 255, 0 } },
	{ 29, ar::colorVector { 0, 255, 0 } },
	{ 30, ar::colorVector { 0, 255, 0 } },
	{ 31, ar::colorVector { 0, 255, 0 } },
	{ 32, ar::colorVector { 0, 255, 0 } },
	{ 33, ar::colorVector { 0, 255, 0 } },
	{ 34, ar::colorVector { 0, 255, 0 } },
	{ 35, ar::colorVector { 0, 255, 0 } },
	{ 36, ar::colorVector { 0, 255, 0 } },
	{ 37, ar::colorVector { 0, 255, 0 } },
	{ 38, ar::colorVector { 0, 255, 0 } },
	{ 39, ar::colorVector { 0, 255, 0 } },
	{ 40, ar::colorVector { 0, 255, 0 } },
	{ 41, ar::colorVector { 0, 0, 255 } },
};

Snake::Snake() : _direction(RIGHT), _pause(true), _classicMode(false),
		 _score(0), _timer(std::time(nullptr)), _time(clock()), _gameOver(false), _map(20, 9),
		 _height(9), _width(20), _movementMap(_height, std::vector<Tile>(_width))
{
	initiateGame();
}

Snake::~Snake()
{
}

void		Snake::initiateGame()
{
	for (size_t i = 0 ; i < _height ; i++) {
		if (i == 0 || i == _height - 1) {
			std::fill(_movementMap[i].begin(), _movementMap[i].end(), WALL);
		} else {
			_movementMap[i][0] = WALL;
			std::fill(_movementMap[i].begin() + 1, _movementMap[i].end() - 1, EMPTY);
			_movementMap[i][_width - 1] = WALL;
		}
		if (i == _height / 2) {
			_movementMap[i][_width / 2 - 2] = TAIL_RIGHT;
			_movementMap[i][_width / 2 - 1] = EMPTY_BODY_RIGHT;
			_movementMap[i][_width / 2] = EMPTY_BODY_RIGHT;
			_movementMap[i][_width / 2 + 1] = CLOSED_MOUTH_RIGHT;
		}
	}
	_snake.insert(_snake.begin(), createSnakePart(_height / 2, _width / 2 + 1, false));
	_snake.insert(_snake.begin(), createSnakePart(_height / 2, _width / 2, false));
	_snake.insert(_snake.begin(), createSnakePart(_height / 2, _width / 2 - 1, false));
	_snake.insert(_snake.begin(), createSnakePart(_height / 2, _width / 2 - 2, false));
	std::srand(std::time(nullptr));
	addPellet();
	updateMap();
}

void		Snake::goUp()
{
	if (_classicMode == true && _snake[_snake.size() - 2].row != _snake.back().row - 1) {
		_direction = UP;
	}
}

void		Snake::goDown()
{
	if (_classicMode == true && _snake[_snake.size() - 2].row != _snake.back().row + 1) {
		_direction = DOWN;
	}
}

void		Snake::goLeft()
{
	if (_classicMode == false) {
		switch (_direction) {
		case UP:
			_direction = LEFT;
			break;
		case DOWN:
			_direction = RIGHT;
			break;
		case LEFT:
			_direction = DOWN;
			break;
		case RIGHT:
			_direction = UP;
			break;
		}
	} else if (_classicMode == true && _snake[_snake.size() - 2].col != _snake.back().col - 1) {
		_direction = LEFT;
	}
}

void		Snake::goRight()
{
	if (_classicMode == false) {
		switch (_direction) {
		case UP:
			_direction = RIGHT;
			break;
		case DOWN:
			_direction = LEFT;
			break;
		case LEFT:
			_direction = UP;
			break;
		case RIGHT:
			_direction = DOWN;
			break;
		}
	} else if (_classicMode == true && _snake[_snake.size() - 2].col != _snake.back().col + 1) {
		_direction = RIGHT;
	}
}

void		Snake::manageKey(const ar::Event &Key)
{
	switch (Key) {
	case ar::AR_UP:
		goUp();
		break;
	case ar::AR_DOWN:
		goDown();
		break;
	case ar::AR_LEFT:
		goLeft();
		break;
	case ar::AR_RIGHT:
		goRight();
		break;
	case ar::AR_PAUSE:
		_pause = !_pause;
		break;
	case ar::AR_ACTION:
		_classicMode = !_classicMode;
		break;
	default:
		break;
	}
}

const std::map<unsigned char, ar::spriteCoords>	&Snake::getSprites() const
{
	return sprites;
}

const std::string	Snake::getSpritesPath() const
{
	std::string	path("./Assets/old_school_snake.png");

	return path;
}

const std::map<unsigned char, ar::colorVector>	&Snake::getColors() const
{
	return colors;
}

int	Snake::refreshScore()
{
	return _score;
}

int	Snake::refreshTimer()
{
	return std::time(nullptr) - _timer;
}

bool	Snake::isGameOver()
{
	return _gameOver;
}

ar::Map	&Snake::getMap()
{
	return _map;
}

Snake::SnakePart	Snake::createSnakePart(std::size_t row, std::size_t col, bool full)
{
	SnakePart	portion;

	portion.row = row;
	portion.col = col;
	portion.full = full;
	return portion;
}

void		Snake::addPellet()
{
	std::size_t	empty_cells = 0;
	int		chosen_cell;
	std::size_t	count;

	for (size_t i = 0 ; i < _height ; i++) {
		empty_cells += std::count(_movementMap[i].begin(), _movementMap[i].end(), EMPTY);
	}
	if (empty_cells == 0)
		return;
	chosen_cell = std::rand() % empty_cells;
	for (count = 0 ; chosen_cell >= std::count(_movementMap[count].begin(), _movementMap[count].end(), EMPTY) ;
	     count++) {
		chosen_cell -= std::count(_movementMap[count].begin(), _movementMap[count].end(), EMPTY);
	}
	for (size_t i = 0 ; i < _width ; i++) {
		if (_movementMap[count][i] == EMPTY && chosen_cell > 1)
			chosen_cell--;
		else if (_movementMap[count][i] == EMPTY) {
			_movementMap[count][i] = PELLET;
			break;
		}
	}
}

void		Snake::updateHead()
{
	if (_snake[_snake.size() - 2].row == _snake.back().row + 1) {
		if (_movementMap[_snake.back().row - 1][_snake.back().col] == PELLET)
			_movementMap[_snake.back().row][_snake.back().col] = OPEN_MOUTH_UP;
		else
			_movementMap[_snake.back().row][_snake.back().col] = CLOSED_MOUTH_UP;
	} else if (_snake[_snake.size() - 2].col == _snake.back().col + 1) {
		if (_movementMap[_snake.back().row][_snake.back().col - 1] == PELLET)
			_movementMap[_snake.back().row][_snake.back().col] = OPEN_MOUTH_LEFT;
		else
			_movementMap[_snake.back().row][_snake.back().col] = CLOSED_MOUTH_LEFT;
	} else if (_snake[_snake.size() - 2].col == _snake.back().col - 1) {
		if (_movementMap[_snake.back().row][_snake.back().col + 1] == PELLET)
			_movementMap[_snake.back().row][_snake.back().col] = OPEN_MOUTH_RIGHT;
		else
			_movementMap[_snake.back().row][_snake.back().col] = CLOSED_MOUTH_RIGHT;
	} else if (_snake[_snake.size() - 2].row == _snake.back().row - 1) {
		if (_movementMap[_snake.back().row + 1][_snake.back().col] == PELLET)
			_movementMap[_snake.back().row][_snake.back().col] = OPEN_MOUTH_DOWN;
		else
			_movementMap[_snake.back().row][_snake.back().col] = CLOSED_MOUTH_DOWN;
	}
}

void		Snake::straightLine()
{
	if (_snake[_snake.size() - 3].row < _snake[_snake.size() - 1].row) {
		if (_snake[_snake.size() - 2].full == false)
			_movementMap[_snake[_snake.size() - 2].row][_snake[_snake.size() - 2].col] =
				EMPTY_BODY_DOWN;
		else if (_snake[_snake.size() - 2].full == true)
			_movementMap[_snake[_snake.size() - 2].row][_snake[_snake.size() - 2].col] =
				FULL_BODY_DOWN;
	} else if (_snake[_snake.size() - 3].row > _snake[_snake.size() - 1].row) {
		if (_snake[_snake.size() - 2].full == false)
			_movementMap[_snake[_snake.size() - 2].row][_snake[_snake.size() - 2].col] =
				EMPTY_BODY_UP;
		else if (_snake[_snake.size() - 2].full == true)
			_movementMap[_snake[_snake.size() - 2].row][_snake[_snake.size() - 2].col] =
				FULL_BODY_UP;
	} else if (_snake[_snake.size() - 3].col < _snake[_snake.size() - 1].col) {
		if (_snake[_snake.size() - 2].full == false)
			_movementMap[_snake[_snake.size() - 2].row][_snake[_snake.size() - 2].col] =
				EMPTY_BODY_RIGHT;
		else if (_snake[_snake.size() - 2].full == true)
			_movementMap[_snake[_snake.size() - 2].row][_snake[_snake.size() - 2].col] =
				FULL_BODY_RIGHT;
	} else if (_snake[_snake.size() - 3].col > _snake[_snake.size() - 1].col) {
		if (_snake[_snake.size() - 2].full == false)
			_movementMap[_snake[_snake.size() - 2].row][_snake[_snake.size() - 2].col] =
				EMPTY_BODY_LEFT;
		else if (_snake[_snake.size() - 2].full == true)
			_movementMap[_snake[_snake.size() - 2].row][_snake[_snake.size() - 2].col] =
				FULL_BODY_LEFT;
	}
}

void		Snake::cornerToTopRight()
{
	if (_snake[_snake.size() - 3].row > _snake[_snake.size() - 2].row) {
		if (_snake[_snake.size() - 2].full == false)
			_movementMap[_snake[_snake.size() - 2].row][_snake[_snake.size() - 2].col] =
				EMPTY_CORNER_DOWN_TO_RIGHT;
		else if (_snake[_snake.size() - 2].full == true)
			_movementMap[_snake[_snake.size() - 2].row][_snake[_snake.size() - 2].col] =
				FULL_CORNER_DOWN_TO_RIGHT;
	} else if (_snake[_snake.size() - 3].col < _snake[_snake.size() - 2].col) {
		if (_snake[_snake.size() - 2].full == false)
			_movementMap[_snake[_snake.size() - 2].row][_snake[_snake.size() - 2].col] =
				EMPTY_CORNER_LEFT_TO_UP;
		else if (_snake[_snake.size() - 2].full == true)
			_movementMap[_snake[_snake.size() - 2].row][_snake[_snake.size() - 2].col] =
				FULL_CORNER_LEFT_TO_UP;
	}
}

void		Snake::cornerToBottomRight()
{
	if (_snake[_snake.size() - 3].row < _snake[_snake.size() - 2].row) {
		if (_snake[_snake.size() - 2].full == false)
			_movementMap[_snake[_snake.size() - 2].row][_snake[_snake.size() - 2].col] =
				EMPTY_CORNER_UP_TO_RIGHT;
		else if (_snake[_snake.size() - 2].full == true)
			_movementMap[_snake[_snake.size() - 2].row][_snake[_snake.size() - 2].col] =
				FULL_CORNER_UP_TO_RIGHT;
	} else if (_snake[_snake.size() - 3].col < _snake[_snake.size() - 2].col) {
		if (_snake[_snake.size() - 2].full == false)
			_movementMap[_snake[_snake.size() - 2].row][_snake[_snake.size() - 2].col] =
				EMPTY_CORNER_LEFT_TO_DOWN;
		else if (_snake[_snake.size() - 2].full == true)
			_movementMap[_snake[_snake.size() - 2].row][_snake[_snake.size() - 2].col] =
				FULL_CORNER_LEFT_TO_DOWN;
	}
}

void		Snake::cornerFromLeftToRight()
{
	if (_snake[_snake.size() - 3].row > _snake[_snake.size() - 1].row) {
		cornerToTopRight();
	} else if (_snake[_snake.size() - 3].row < _snake[_snake.size() - 1].row) {
		cornerToBottomRight();
	}
}

void		Snake::cornerToTopLeft()
{
	if (_snake[_snake.size() - 3].row > _snake[_snake.size() - 2].row) {
		if (_snake[_snake.size() - 2].full == false)
			_movementMap[_snake[_snake.size() - 2].row][_snake[_snake.size() - 2].col] =
				EMPTY_CORNER_DOWN_TO_LEFT;
		else if (_snake[_snake.size() - 2].full == true)
			_movementMap[_snake[_snake.size() - 2].row][_snake[_snake.size() - 2].col] =
				FULL_CORNER_DOWN_TO_LEFT;
	} else if (_snake[_snake.size() - 3].col > _snake[_snake.size() - 2].col) {
		if (_snake[_snake.size() - 2].full == false)
			_movementMap[_snake[_snake.size() - 2].row][_snake[_snake.size() - 2].col] =
				EMPTY_CORNER_RIGHT_TO_UP;
		else if (_snake[_snake.size() - 2].full == true)
			_movementMap[_snake[_snake.size() - 2].row][_snake[_snake.size() - 2].col] =
				FULL_CORNER_RIGHT_TO_UP;
	}
}

void		Snake::cornerToBottomLeft()
{
	if (_snake[_snake.size() - 3].row < _snake[_snake.size() - 2].row) {
		if (_snake[_snake.size() - 2].full == false)
			_movementMap[_snake[_snake.size() - 2].row][_snake[_snake.size() - 2].col] =
				EMPTY_CORNER_UP_TO_LEFT;
		else if (_snake[_snake.size() - 2].full == true)
			_movementMap[_snake[_snake.size() - 2].row][_snake[_snake.size() - 2].col] =
				FULL_CORNER_UP_TO_LEFT;
	} else if (_snake[_snake.size() - 3].col > _snake[_snake.size() - 2].col) {
		if (_snake[_snake.size() - 2].full == false)
			_movementMap[_snake[_snake.size() - 2].row][_snake[_snake.size() - 2].col] =
				EMPTY_CORNER_RIGHT_TO_DOWN;
		else if (_snake[_snake.size() - 2].full == true)
			_movementMap[_snake[_snake.size() - 2].row][_snake[_snake.size() - 2].col] =
				FULL_CORNER_RIGHT_TO_DOWN;
	}
}

void		Snake::cornerFromRightToLeft()
{
	if (_snake[_snake.size() - 3].row > _snake[_snake.size() - 1].row) {
		cornerToTopLeft();
	} else if (_snake[_snake.size() - 3].row < _snake[_snake.size() - 1].row) {
		cornerToBottomLeft();
	}
}

void		Snake::corner()
{
	if (_snake[_snake.size() - 3].col < _snake[_snake.size() - 1].col) {
		cornerFromLeftToRight();
	} else if (_snake[_snake.size() - 3].col > _snake[_snake.size() - 1].col) {
		cornerFromRightToLeft();
	}
}

void		Snake::updateFirstBodyPart()
{
	if (_snake[_snake.size() - 3].row == _snake[_snake.size() - 1].row ||
	    _snake[_snake.size() - 3].col == _snake[_snake.size() - 1].col) {
		straightLine();
	} else {
		corner();
	}
}

void		Snake::updateTail(Tile tail)
{
	if (tail == EMPTY_BODY_UP || tail == FULL_BODY_UP ||
	    tail == EMPTY_CORNER_RIGHT_TO_UP || tail == EMPTY_CORNER_LEFT_TO_UP ||
	    tail == FULL_CORNER_RIGHT_TO_UP || tail == FULL_CORNER_LEFT_TO_UP)
		_movementMap[_snake.front().row][_snake.front().col] = TAIL_UP;
	if (tail == EMPTY_BODY_LEFT || tail == FULL_BODY_LEFT ||
	    tail == EMPTY_CORNER_DOWN_TO_LEFT || tail == EMPTY_CORNER_UP_TO_LEFT ||
	    tail == FULL_CORNER_DOWN_TO_LEFT || tail == FULL_CORNER_UP_TO_LEFT)
		_movementMap[_snake.front().row][_snake.front().col] = TAIL_LEFT;
	if (tail == EMPTY_BODY_RIGHT || tail == FULL_BODY_RIGHT ||
	    tail == EMPTY_CORNER_DOWN_TO_RIGHT || tail == EMPTY_CORNER_UP_TO_RIGHT ||
	    tail == FULL_CORNER_DOWN_TO_RIGHT || tail == FULL_CORNER_UP_TO_RIGHT)
		_movementMap[_snake.front().row][_snake.front().col] = TAIL_RIGHT;
	if (tail == EMPTY_BODY_DOWN || tail == FULL_BODY_DOWN ||
	    tail == EMPTY_CORNER_RIGHT_TO_DOWN || tail == EMPTY_CORNER_LEFT_TO_DOWN ||
	    tail == FULL_CORNER_RIGHT_TO_DOWN || tail == FULL_CORNER_LEFT_TO_DOWN)
		_movementMap[_snake.front().row][_snake.front().col] = TAIL_DOWN;
}

void		Snake::updateSnake(Tile tile, std::size_t row, std::size_t col)
{
	if (tile == PELLET) {
		_snake.insert(_snake.end(), createSnakePart(row, col, true));
		updateHead();
		updateFirstBodyPart();
		addPellet();
		_score += 100;
	} else {
		_movementMap[_snake.front().row][_snake.front().col] = EMPTY;
		_snake.erase(_snake.begin());
		updateTail(_movementMap[_snake.front().row][_snake.front().col]);
		_snake.insert(_snake.end(), createSnakePart(row, col, false));
		updateHead();
		updateFirstBodyPart();
	}
}

bool		Snake::possibleDestination(Tile tile)
{
	if (tile == EMPTY || tile == PELLET || tile == TAIL_UP ||
	    tile == TAIL_LEFT || tile == TAIL_RIGHT || tile == TAIL_DOWN)
		return true;
	return false;
}

void	Snake::updateMap()
{
	for (size_t x = 0 ; x < _height ; x++) {
		for (size_t y = 0 ; y < _width ; y++) {
			_map[x][y] = _movementMap[x][y];
		}
	}
}

void	Snake::loop()
{
	if (clock() - _time < 300000 || _pause == true)
		return;
	if (_direction == UP &&
	    possibleDestination(_movementMap[_snake.back().row - 1][_snake.back().col]) == true) {
		updateSnake(_movementMap[_snake.back().row - 1][_snake.back().col],
			    _snake.back().row - 1, _snake.back().col);
	} else if (_direction == DOWN &&
		   possibleDestination(_movementMap[_snake.back().row + 1][_snake.back().col]) == true) {
		updateSnake(_movementMap[_snake.back().row + 1][_snake.back().col],
			    _snake.back().row + 1, _snake.back().col);
	} else if (_direction == LEFT &&
		   possibleDestination(_movementMap[_snake.back().row][_snake.back().col - 1]) == true) {
		updateSnake(_movementMap[_snake.back().row][_snake.back().col - 1],
			    _snake.back().row, _snake.back().col - 1);
	} else if (_direction == RIGHT &&
		   possibleDestination(_movementMap[_snake.back().row][_snake.back().col + 1]) == true) {
		updateSnake(_movementMap[_snake.back().row][_snake.back().col + 1],
			    _snake.back().row, _snake.back().col + 1);
	} else
		_gameOver = true;
	updateMap();
	_time = clock();
}

const std::string	Snake::getGameName() const
{
	std::string	name("Nibbler");

	return name;
}

void	Snake::setPause()
{
	_pause = true;
}

extern "C" Snake *createGame()
{
	return new Snake();
}

extern "C" void destroyGame(Snake *snake)
{
	delete snake;
}

/*void		Snake::bigDisplay()
{
	const std::vector<std::vector<std::string> >	display =
		{{"++++++++", "++++++++", "++++++++", "++++++++"},
		 {"        ", "        ", "        ", "        "},
		 {"        ", "XX    XX", "  XXXX  ", "XX  XX  "},
		 {"  XX  XX", "    XX  ", "    XXXX", "  XX    "},
		 {"XX  XX  ", "  XX    ", "XXXX    ", "    XX  "},
		 {"XX  XX  ", "  XXXX  ", "XX    XX", "        "},
		 {"        ", "  XXXX  ", "  XXXX  ", "XX  XX  "},
		 {"      XX", "  XXXX  ", "  XXXXXX", "        "},
		 {"XX      ", "  XXXX  ", "XXXXXX  ", "        "},
		 {"XX  XX  ", "  XXXX  ", "  XXXX  ", "        "},
		 {"  XXXX  ", "    XX  ", "  XX    ", "  XXXX  "},
		 {"        ", "XX  XXXX", "XXXX  XX", "        "},
		 {"        ", "XXXX  XX", "XX  XXXX", "        "},
		 {"  XXXX  ", "  XX    ", "    XX  ", "  XXXX  "},
		 {"  XXXX  ", "XX  XXXX", "XXXX  XX", "  XXXX  "},
		 {"  XXXX  ", "XX  XXXX", "XXXX  XX", "  XXXX  "},
		 {"  XXXX  ", "XXXX  XX", "XX  XXXX", "  XXXX  "},
		 {"  XXXX  ", "XXXX  XX", "XX  XXXX", "  XXXX  "},
		 {"  XXXX  ", "  XX  XX", "    XXXX", "        "},
		 {"  XXXX  ", "XX  XX  ", "XXXX    ", "        "},
		 {"  XXXX  ", "XX  XX  ", "XXXX    ", "        "},
		 {"        ", "XXXX    ", "XX  XX  ", "  XXXX  "},
		 {"  XXXX  ", "  XX  XX", "    XXXX", "        "},
		 {"        ", "    XXXX", "  XX  XX", "  XXXX  "},
		 {"        ", "    XXXX", "  XX  XX", "  XXXX  "},
		 {"        ", "XXXX    ", "XX  XX  ", "  XXXX  "},
		 {"  XXXXXX", "  XX  XX", "    XXXX", "        "},
		 {"XXXXXX  ", "XX  XX  ", "XXXX    ", "        "},
		 {"XXXXXX  ", "XX  XX  ", "XXXX    ", "        "},
		 {"        ", "XXXX    ", "XX  XX  ", "XXXXXX  "},
		 {"  XXXXXX", "  XX  XX", "    XXXX", "        "},
		 {"        ", "    XXXX", "  XX  XX", "  XXXXXX"},
		 {"        ", "    XXXX", "  XX  XX", "  XXXXXX"},
		 {"        ", "XXXX    ", "XX  XX  ", "XXXXXX  "},
		 {"  XXXX  ", "  XXXX  ", "    XX  ", "    XX  "},
		 {"        ", "XXXX    ", "XXXXXXXX", "        "},
		 {"        ", "    XXXX", "XXXXXXXX", "        "},
		 {"    XX  ", "    XX  ", "  XXXX  ", "  XXXX  "},
		 {"        ", "  XXXX  ", "  XXXX  ", "        "}};

	for (size_t i = 0 ; i < _height ; i++) {
		for (size_t j = 0 ; j < _width ; j++)
			std::cout << display[_movementMap[i][j]][0];
		std::cout << std::endl;
		for (size_t j = 0 ; j < _width ; j++)
			std::cout << display[_movementMap[i][j]][1];
		std::cout << std::endl;
		for (size_t j = 0 ; j < _width ; j++)
			std::cout << display[_movementMap[i][j]][2];
		std::cout << std::endl;
		for (size_t j = 0 ; j < _width ; j++)
			std::cout << display[_movementMap[i][j]][3];
		std::cout << std::endl;
		}*/
	/*for (size_t x = 0 ; x < _height ; x++) {
		for (size_t y = 0 ; y < _width ; y++) {
			std::cout << _map[x][y];
		}
		std::cout << std::endl;
		}*/

	//}
