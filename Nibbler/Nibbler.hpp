//
// EPITECH PROJECT, 2018
// arcade
// File description:
// Nibbler Class
//

#ifndef		NIBBLER_HPP_
#define		NIBBLER_HPP_

#include	<map>
#include	<vector>

struct		SnakePart {
	std::size_t	row;
	std::size_t	col;
	bool		full;
};

enum		direction {
	LEFT,
	RIGHT,
	UP,
	DOWN
};

enum		tile {
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


class		Nibbler
{
public:
	Nibbler();
	~Nibbler();

	SnakePart	createSnakePart(std::size_t row, std::size_t col, bool full);
	void		addPellet();
	void		updateHead();
	void		straightLine();
	void		cornerToTopRight();
	void		cornerToBottomRight();
	void		cornerFromLeftToRight();
	void		cornerToTopLeft();
	void		cornerToBottomLeft();
	void		cornerFromRightToLeft();
	void		corner();
	void		updateFirstBodyPart();
	void		updateTail(tile tail);
	void		updateSnake(tile tile, std::size_t row, std::size_t col);
	bool		possibleDestination(tile tile);
	bool		move();
	void		setDirection(direction dir);
	//void		pause() const;
	void		displayMap() const;
	void		bigDisplay() const;
	void		demo();
	//void		menu() const;

private:
	std::size_t			_snake_length;
	const std::size_t		_map_height;
	const std::size_t		_map_width;
	std::size_t			_score;
	std::vector<std::vector<tile> >	_map;
	std::vector<SnakePart>		_snake;
	direction			_direction;
	bool				_full;
};

#endif		/* !NIBBLER_HPP_ */
