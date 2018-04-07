/*
** EPITECH PROJECT, 2018
** cpp_arcade
** File description:
** Created by martin.januario@epitech.eu,
*/

#ifndef CPP_ARCADE_MANAGEROCKET_HPP
# define CPP_ARCADE_MANAGEROCKET_HPP

# include "AbstractHitBox.hpp"

class ManageRocket : public AbstractHitBox {
	public:
	// Constructor / Destructor
	ManageRocket(double posX, double posY, double speed, DirectionObj dir);

	// Operator Copy & copy constructor
	ManageRocket(const ManageRocket &other);
	ManageRocket &operator=(const ManageRocket &other);

	void moveForwardRocket(void);

	// Setter
	void setPosX(double posX);
	void setPosY(double posY);
	void setSpeed(double speed);
	void setDirection(DirectionObj dir);

	// Getter
	double getPosX() const;
	double getPosY() const;
	double getSpeed() const;
	DirectionObj getDirection() const;

	protected:

	private:
	double _posX;
	double _posY;

	double _speed;
	DirectionObj _dir;

};

#endif //CPP_ARCADE_MANAGEROCKET_HPP
