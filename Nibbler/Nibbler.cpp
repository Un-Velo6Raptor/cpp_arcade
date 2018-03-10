//
// EPITECH PROJECT, 2018
// arcade
// File description:
// Nibbler Class
//

#include	<algorithm>
#include	<iostream>
#include	<cstdlib>
#include	<ctime>
#include	"Nibbler.hpp"

Nibbler::Nibbler() : _snake_length(4), _map_height(9), _map_width(20), _score(0),
		     _map(_map_height, std::vector<tile>(_map_width)),
		     _direction(RIGHT), _full(0)
{
	for (size_t i = 0 ; i < _map_height ; i++) {
		if (i == 0 || i == _map_height - 1) {
			std::fill(_map[i].begin(), _map[i].end(), WALL);
		} else {
			_map[i][0] = WALL;
			std::fill(_map[i].begin() + 1, _map[i].end() - 1, EMPTY);
			_map[i][_map_width - 1] = WALL;
		}
		if (i == _map_height / 2) {
			_map[i][_map_width / 2 - 2] = TAIL_RIGHT;
			_map[i][_map_width / 2 - 1] = EMPTY_BODY_RIGHT;
			_map[i][_map_width / 2] = EMPTY_BODY_RIGHT;
			_map[i][_map_width / 2 + 1] = CLOSED_MOUTH_RIGHT;
		}
	}
	_snake.insert(_snake.begin(), createSnakePart(_map_height / 2, _map_width / 2 + 1, false));
	_snake.insert(_snake.begin(), createSnakePart(_map_height / 2, _map_width / 2, false));
	_snake.insert(_snake.begin(), createSnakePart(_map_height / 2, _map_width / 2 - 1, false));
	_snake.insert(_snake.begin(), createSnakePart(_map_height / 2, _map_width / 2 - 2, false));
	std::srand(std::time(nullptr));
	addPellet();
}

Nibbler::~Nibbler()
{
}

SnakePart	Nibbler::createSnakePart(std::size_t row, std::size_t col, bool full)
{
	SnakePart	portion;

	portion.row = row;
	portion.col = col;
	portion.full = full;
	return portion;
}

void		Nibbler::addPellet()
{
	std::size_t	empty_cells = 0;
	std::size_t	chosen_cell;
	std::size_t	count;

	for (size_t i = 0 ; i < _map_height ; i++) {
		empty_cells += std::count(_map[i].begin(), _map[i].end(), EMPTY);
	}
	if (empty_cells == 0)
		return;
	chosen_cell = std::rand() % empty_cells;
	for (count = 0 ; chosen_cell >= std::count(_map[count].begin(), _map[count].end(), EMPTY) ;
	     count++) {
		chosen_cell -= std::count(_map[count].begin(), _map[count].end(), EMPTY);
	}
	for (size_t i = 0 ; i < _map_width ; i++) {
		if (_map[count][i] == EMPTY && chosen_cell > 1)
			chosen_cell--;
		else if (_map[count][i] == EMPTY) {
			_map[count][i] = PELLET;
			break;
		}
	}
}

void		Nibbler::updateHead()
{
	if (_snake[_snake.size() - 2].row == _snake.back().row + 1) {
		if (_map[_snake.back().row - 1][_snake.back().col] == PELLET)
			_map[_snake.back().row][_snake.back().col] = OPEN_MOUTH_UP;
		else
			_map[_snake.back().row][_snake.back().col] = CLOSED_MOUTH_UP;
	} else if (_snake[_snake.size() - 2].col == _snake.back().col + 1) {
		if (_map[_snake.back().row][_snake.back().col - 1] == PELLET)
			_map[_snake.back().row][_snake.back().col] = OPEN_MOUTH_LEFT;
		else
			_map[_snake.back().row][_snake.back().col] = CLOSED_MOUTH_LEFT;
	} else if (_snake[_snake.size() - 2].col == _snake.back().col - 1) {
		if (_map[_snake.back().row][_snake.back().col + 1] == PELLET)
			_map[_snake.back().row][_snake.back().col] = OPEN_MOUTH_RIGHT;
		else
			_map[_snake.back().row][_snake.back().col] = CLOSED_MOUTH_RIGHT;
	} else if (_snake[_snake.size() - 2].row == _snake.back().row - 1) {
		if (_map[_snake.back().row + 1][_snake.back().col] == PELLET)
			_map[_snake.back().row][_snake.back().col] = OPEN_MOUTH_DOWN;
		else
			_map[_snake.back().row][_snake.back().col] = CLOSED_MOUTH_DOWN;
	}
}

void		Nibbler::straightLine()
{
	if (_snake[_snake.size() - 3].row < _snake[_snake.size() - 1].row) {
		if (_snake[_snake.size() - 2].full == false)
			_map[_snake[_snake.size() - 2].row][_snake[_snake.size() - 2].col] =
				EMPTY_BODY_DOWN;
		else if (_snake[_snake.size() - 2].full == true)
			_map[_snake[_snake.size() - 2].row][_snake[_snake.size() - 2].col] =
				FULL_BODY_DOWN;
	} else if (_snake[_snake.size() - 3].row > _snake[_snake.size() - 1].row) {
		if (_snake[_snake.size() - 2].full == false)
			_map[_snake[_snake.size() - 2].row][_snake[_snake.size() - 2].col] =
				EMPTY_BODY_UP;
		else if (_snake[_snake.size() - 2].full == true)
			_map[_snake[_snake.size() - 2].row][_snake[_snake.size() - 2].col] =
				FULL_BODY_UP;
	} else if (_snake[_snake.size() - 3].col < _snake[_snake.size() - 1].col) {
		if (_snake[_snake.size() - 2].full == false)
			_map[_snake[_snake.size() - 2].row][_snake[_snake.size() - 2].col] =
				EMPTY_BODY_RIGHT;
		else if (_snake[_snake.size() - 2].full == true)
			_map[_snake[_snake.size() - 2].row][_snake[_snake.size() - 2].col] =
				FULL_BODY_RIGHT;
	} else if (_snake[_snake.size() - 3].col > _snake[_snake.size() - 1].col) {
		if (_snake[_snake.size() - 2].full == false)
			_map[_snake[_snake.size() - 2].row][_snake[_snake.size() - 2].col] =
				EMPTY_BODY_LEFT;
		else if (_snake[_snake.size() - 2].full == true)
			_map[_snake[_snake.size() - 2].row][_snake[_snake.size() - 2].col] =
				FULL_BODY_LEFT;
	}
}

void		Nibbler::cornerToTopRight()
{
	if (_snake[_snake.size() - 3].row > _snake[_snake.size() - 2].row) {
		if (_snake[_snake.size() - 2].full == false)
			_map[_snake[_snake.size() - 2].row][_snake[_snake.size() - 2].col] =
				EMPTY_CORNER_DOWN_TO_RIGHT;
		else if (_snake[_snake.size() - 2].full == true)
			_map[_snake[_snake.size() - 2].row][_snake[_snake.size() - 2].col] =
				FULL_CORNER_DOWN_TO_RIGHT;
	} else if (_snake[_snake.size() - 3].col < _snake[_snake.size() - 2].col) {
		if (_snake[_snake.size() - 2].full == false)
			_map[_snake[_snake.size() - 2].row][_snake[_snake.size() - 2].col] =
				EMPTY_CORNER_LEFT_TO_UP;
		else if (_snake[_snake.size() - 2].full == true)
			_map[_snake[_snake.size() - 2].row][_snake[_snake.size() - 2].col] =
				FULL_CORNER_LEFT_TO_UP;
	}
}

void		Nibbler::cornerToBottomRight()
{
	if (_snake[_snake.size() - 3].row < _snake[_snake.size() - 2].row) {
		if (_snake[_snake.size() - 2].full == false)
			_map[_snake[_snake.size() - 2].row][_snake[_snake.size() - 2].col] =
				EMPTY_CORNER_UP_TO_RIGHT;
		else if (_snake[_snake.size() - 2].full == true)
			_map[_snake[_snake.size() - 2].row][_snake[_snake.size() - 2].col] =
				FULL_CORNER_UP_TO_RIGHT;
	} else if (_snake[_snake.size() - 3].col < _snake[_snake.size() - 2].col) {
		if (_snake[_snake.size() - 2].full == false)
			_map[_snake[_snake.size() - 2].row][_snake[_snake.size() - 2].col] =
				EMPTY_CORNER_LEFT_TO_DOWN;
		else if (_snake[_snake.size() - 2].full == true)
			_map[_snake[_snake.size() - 2].row][_snake[_snake.size() - 2].col] =
				FULL_CORNER_LEFT_TO_DOWN;
	}
}

void		Nibbler::cornerFromLeftToRight()
{
	if (_snake[_snake.size() - 3].row > _snake[_snake.size() - 1].row) {
		cornerToTopRight();
	} else if (_snake[_snake.size() - 3].row < _snake[_snake.size() - 1].row) {
		cornerToBottomRight();
	}
}

void		Nibbler::cornerToTopLeft()
{
	if (_snake[_snake.size() - 3].row > _snake[_snake.size() - 2].row) {
		if (_snake[_snake.size() - 2].full == false)
			_map[_snake[_snake.size() - 2].row][_snake[_snake.size() - 2].col] =
				EMPTY_CORNER_DOWN_TO_LEFT;
		else if (_snake[_snake.size() - 2].full == true)
			_map[_snake[_snake.size() - 2].row][_snake[_snake.size() - 2].col] =
				FULL_CORNER_DOWN_TO_LEFT;
	} else if (_snake[_snake.size() - 3].col > _snake[_snake.size() - 2].col) {
		if (_snake[_snake.size() - 2].full == false)
			_map[_snake[_snake.size() - 2].row][_snake[_snake.size() - 2].col] =
				EMPTY_CORNER_RIGHT_TO_UP;
		else if (_snake[_snake.size() - 2].full == true)
			_map[_snake[_snake.size() - 2].row][_snake[_snake.size() - 2].col] =
				FULL_CORNER_RIGHT_TO_UP;
	}
}

void		Nibbler::cornerToBottomLeft()
{
	if (_snake[_snake.size() - 3].row < _snake[_snake.size() - 2].row) {
		if (_snake[_snake.size() - 2].full == false)
			_map[_snake[_snake.size() - 2].row][_snake[_snake.size() - 2].col] =
				EMPTY_CORNER_UP_TO_LEFT;
		else if (_snake[_snake.size() - 2].full == true)
			_map[_snake[_snake.size() - 2].row][_snake[_snake.size() - 2].col] =
				FULL_CORNER_UP_TO_LEFT;
	} else if (_snake[_snake.size() - 3].col > _snake[_snake.size() - 2].col) {
		if (_snake[_snake.size() - 2].full == false)
			_map[_snake[_snake.size() - 2].row][_snake[_snake.size() - 2].col] =
				EMPTY_CORNER_RIGHT_TO_DOWN;
		else if (_snake[_snake.size() - 2].full == true)
			_map[_snake[_snake.size() - 2].row][_snake[_snake.size() - 2].col] =
				FULL_CORNER_RIGHT_TO_DOWN;
	}
}

void		Nibbler::cornerFromRightToLeft()
{
	if (_snake[_snake.size() - 3].row > _snake[_snake.size() - 1].row) {
		cornerToTopLeft();
	} else if (_snake[_snake.size() - 3].row < _snake[_snake.size() - 1].row) {
		cornerToBottomLeft();
	}
}

void		Nibbler::corner()
{
	if (_snake[_snake.size() - 3].col < _snake[_snake.size() - 1].col) {
		cornerFromLeftToRight();
	} else if (_snake[_snake.size() - 3].col > _snake[_snake.size() - 1].col) {
		cornerFromRightToLeft();
	}
}

void		Nibbler::updateFirstBodyPart()
{
	if (_snake[_snake.size() - 3].row == _snake[_snake.size() - 1].row ||
	    _snake[_snake.size() - 3].col == _snake[_snake.size() - 1].col) {
		straightLine();
	} else {
		corner();
	}
}

void		Nibbler::updateTail(tile tail)
{
	if (tail == EMPTY_BODY_UP || tail == FULL_BODY_UP ||
	    tail == EMPTY_CORNER_RIGHT_TO_UP || tail == EMPTY_CORNER_LEFT_TO_UP ||
	    tail == FULL_CORNER_RIGHT_TO_UP || tail == FULL_CORNER_LEFT_TO_UP)
		_map[_snake.front().row][_snake.front().col] = TAIL_UP;
	if (tail == EMPTY_BODY_LEFT || tail == FULL_BODY_LEFT ||
	    tail == EMPTY_CORNER_DOWN_TO_LEFT || tail == EMPTY_CORNER_UP_TO_LEFT ||
	    tail == FULL_CORNER_DOWN_TO_LEFT || tail == FULL_CORNER_UP_TO_LEFT)
		_map[_snake.front().row][_snake.front().col] = TAIL_LEFT;
	if (tail == EMPTY_BODY_RIGHT || tail == FULL_BODY_RIGHT ||
	    tail == EMPTY_CORNER_DOWN_TO_RIGHT || tail == EMPTY_CORNER_UP_TO_RIGHT ||
	    tail == FULL_CORNER_DOWN_TO_RIGHT || tail == FULL_CORNER_UP_TO_RIGHT)
		_map[_snake.front().row][_snake.front().col] = TAIL_RIGHT;
	if (tail == EMPTY_BODY_DOWN || tail == FULL_BODY_DOWN ||
	    tail == EMPTY_CORNER_RIGHT_TO_DOWN || tail == EMPTY_CORNER_LEFT_TO_DOWN ||
	    tail == FULL_CORNER_RIGHT_TO_DOWN || tail == FULL_CORNER_LEFT_TO_DOWN)
		_map[_snake.front().row][_snake.front().col] = TAIL_DOWN;
}

void		Nibbler::updateSnake(tile tile, std::size_t row, std::size_t col)
{
	if (tile == PELLET) {
		_snake.insert(_snake.end(), createSnakePart(row, col, true));
		updateHead();
		updateFirstBodyPart();
		addPellet();
		_score++;
	} else {
		_map[_snake.front().row][_snake.front().col] = EMPTY;
		_snake.erase(_snake.begin());
		updateTail(_map[_snake.front().row][_snake.front().col]);
		_snake.insert(_snake.end(), createSnakePart(row, col, false));
		updateHead();
		updateFirstBodyPart();
	}
}

bool		Nibbler::possibleDestination(tile tile)
{
	if (tile == EMPTY || tile == PELLET || tile == TAIL_UP ||
	    tile == TAIL_LEFT || tile == TAIL_RIGHT || tile == TAIL_DOWN)
		return true;
	return false;
}

bool		Nibbler::move()
{
	if (_direction == UP &&
	    possibleDestination(_map[_snake.back().row - 1][_snake.back().col]) == true) {
		updateSnake(_map[_snake.back().row - 1][_snake.back().col],
			    _snake.back().row - 1, _snake.back().col);
	} else if (_direction == DOWN &&
		   possibleDestination(_map[_snake.back().row + 1][_snake.back().col]) == true) {
		updateSnake(_map[_snake.back().row + 1][_snake.back().col],
			    _snake.back().row + 1, _snake.back().col);
	} else if (_direction == LEFT &&
		   possibleDestination(_map[_snake.back().row][_snake.back().col - 1]) == true) {
		updateSnake(_map[_snake.back().row][_snake.back().col - 1],
			    _snake.back().row, _snake.back().col - 1);
	} else if (_direction == RIGHT &&
		   possibleDestination(_map[_snake.back().row][_snake.back().col + 1]) == true) {
		updateSnake(_map[_snake.back().row][_snake.back().col + 1],
			    _snake.back().row, _snake.back().col + 1);
	} else
		return false;
	return true;
}

void		Nibbler::setDirection(direction dir)
{
	if (dir == UP && _snake[_snake.size() - 2].row != _snake.back().row - 1) {
		_direction = UP;
	} else if (dir == LEFT && _snake[_snake.size() - 2].col != _snake.back().col - 1) {
		_direction = LEFT;
	} else if (dir == RIGHT && _snake[_snake.size() - 2].col != _snake.back().col + 1) {
		_direction = RIGHT;
	} else if (dir == DOWN && _snake[_snake.size() - 2].row != _snake.back().row + 1) {
		_direction = DOWN;
	}
}

void		Nibbler::displayMap() const
{
	std::string	display = "X V><A****|--|oooo++++++++oooooooo....&";

	for (size_t i = 0 ; i < _map_height ; i++) {
		for (size_t j = 0 ; j < _map_width ; j++) {
			std::cout << display[_map[i][j]];
		}
		std::cout << std::endl;
	}
}

void		Nibbler::bigDisplay() const
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

	for (size_t i = 0 ; i < _map_height ; i++) {
		for (size_t j = 0 ; j < _map_width ; j++)
			std::cout << display[_map[i][j]][0];
		std::cout << std::endl;
		for (size_t j = 0 ; j < _map_width ; j++)
			std::cout << display[_map[i][j]][1];
		std::cout << std::endl;
		for (size_t j = 0 ; j < _map_width ; j++)
			std::cout << display[_map[i][j]][2];
		std::cout << std::endl;
		for (size_t j = 0 ; j < _map_width ; j++)
			std::cout << display[_map[i][j]][3];
		std::cout << std::endl;
	}
}

void		Nibbler::demo()
{
	if (_snake.back().row == 1) {
		if (_snake.back().col == 1)
			setDirection(DOWN);
		else
			setDirection(LEFT);
	} else if (_snake.back().col % 2 == 1) {
		if (_snake.back().row == _map.size() - 2)
			setDirection(RIGHT);
		else
			setDirection(DOWN);
	} else if (_snake.back().col % 2 == 0) {
		if (_snake.back().row == 2 && _snake.back().col != _map[0].size() - 2)
			setDirection(RIGHT);
		else
			setDirection(UP);
	}
}
