/*
** EPITECH PROJECT, 2018
** cpp_arcade
** File description:
** Created by martin.januario@epitech.eu,
*/

#include "ManageMap.hpp"
#include "MapException.hpp"

#include "ManageEnemy.hpp"
#include "EnemyException.hpp"

int main(void)
{
	ManageMap *tmp = new ManageMap(10, 10);

	try {
		tmp->generateMap(20);
		tmp->displayMap();

		ManageEnemy *enemy1 = new ManageEnemy(tmp, 0, 2, 0.5, 100);
		enemy1->LaunchRocket();
		enemy1->LaunchRocket();
		enemy1->LaunchRocket();

		enemy1->AdvanceAllRocket();
		enemy1->AdvanceAllRocket();
		enemy1->AdvanceAllRocket();

		(void)enemy1;
		while (1) {
			enemy1->FollowTheRail();
			std::cout << "enemy=(" << enemy1->getPosX() << ", " << enemy1->getPosY() << ") -" << tmp->getMap()[enemy1->getPosY()][enemy1->getPosX()] << std::endl;
		}

		delete(enemy1);
	} catch (MapException const &error) {
		std::cout << "From " << error.getName() << ":" << std::endl;
		std::cout << error.what() << std::endl;
		return 84;
	} catch (EnemyException const &error) {
		std::cout << "From " << error.getName() << ":" << std::endl;
		std::cout << error.what() << std::endl;
		return 84;
	}
	return (0);
}