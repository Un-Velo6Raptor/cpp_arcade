/*
** EPITECH PROJECT, 2018
** cpp_arcade
** File description:
** Created by martin.januario@epitech.eu,
*/

#ifndef CPP_ARCADE_MANAGEENEMY_HPP
# define CPP_ARCADE_MANAGEENEMY_HPP

# include <vector>
# include "ManageMap.hpp"
# include "ManageRocket.hpp"
# include "AbstractHitBox.hpp"

class ManageEnemy : public AbstractHitBox {
	public:
	// Constructor
	ManageEnemy(ManageMap *mapGame, double posX, double posY, double speed, std::size_t rateOfFire);
	~ManageEnemy();

	// Copy constructor / Operator copy
	ManageEnemy &operator=(ManageEnemy &other);
	ManageEnemy(ManageEnemy &other);

	// Getter
	double getPosY(void) const;
	double getPosX(void) const;


	// EnemyRocketManage
	DirectionObj OrientateRocketLauncher(void);
	void LaunchRocket(void);
	void AdvanceAllRocket(void);

	// EnemyMove
	void FollowTheRail(void);
	DirectionObj OrientateTheDirEnemy(void);

	protected:
	// EnemyMove
	void MoveVerticaly(void);
	void MoveHorizontaly(void);


	private:
	ManageMap *_mapGame;

	DirectionObj _dirEnemyMove;
	double _posX;
	double _posY;
	double _speed;
	std::size_t _rateOfFire; // One rocket every _rateOfFire ms

	std::vector<ManageRocket *> _rocketFire;
	DirectionObj _dirRocket;
};

#endif //CPP_ARCADE_MANAGEENEMY_HPP
