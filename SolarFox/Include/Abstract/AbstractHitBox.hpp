/*
** EPITECH PROJECT, 2018
** cpp_arcade
** File description:
** Created by martin.januario@epitech.eu,
*/

#ifndef CPP_ARCADE_ABSTRACTHITBOX_HPP
# define CPP_ARCADE_ABSTRACTHITBOX_HPP

# include <cstddef>
# include "Enum.hpp"

class AbstractHitBox {
	public:
	AbstractHitBox(std::size_t sizeX, std::size_t sizeY);
	virtual ~AbstractHitBox() = default;

	std::size_t getSizeX() const;
	std::size_t getSizeY() const;

	void setSizeX(std::size_t sizeX);
	void setSizeY(std::size_t sizeY);

	protected:

	private:
	std::size_t _sizeX;
	std::size_t _sizeY;
};

#endif //CPP_ARCADE_ABSTRACTHITBOX_HPP
