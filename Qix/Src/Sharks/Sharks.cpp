/*
** EPITECH PROJECT, 2018
** cpp_arcade
** File description:
** Created by martin.januario@epitech.eu,
*/

#include "Sharks.hpp"

ManageSharks::ManageSharks(ManageMap &manageMap, bool randOk)
{
	initSharksOnTheMap(manageMap, randOk);
}

ManageSharks::~ManageSharks()
{
}