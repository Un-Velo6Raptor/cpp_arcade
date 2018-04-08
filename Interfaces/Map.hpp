/*
** EPITECH PROJECT, 2018
** arcade
** File description:
** Map class
*/

#ifndef CPP_ARCADE_MAP_HPP
# define CPP_ARCADE_MAP_HPP

namespace ar {
	class Map {
	public:
		~Map();
		Map(int _height, int _width);

		int getHeight() const;
		int getWidth() const;
		int getPlayerX() const;
		int getPlayerY() const;
		void setPlayerX(int x);
		void setPlayerY(int y);
		int *&operator[](int x);
	private:
		int **_map;
		int _height;
		int _width;
		int _playerPosX;
		int _playerPosY;
	};
}

#endif //CPP_ARCADE_MAP_HPP
