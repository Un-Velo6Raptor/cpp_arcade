/*
** EPITECH PROJECT, 2018
** cpp_arcade
** File description:
** Created by sahel.lucas-saoudi@epitech.eu,
*/

#include <dlfcn.h>
#include "DLoader.hpp"

ar::DLoader::DLoader(std::string const &path)
{
	_dl = dlopen(path.c_str(), RTLD_NOW);
	char *error = dlerror();

	if (error) {
		std::cerr << error << std::endl;
		throw std::invalid_argument("Error when opening lib " + path);
	}
}

ar::DLoader::~DLoader()
{
	if (_dl)
		dlclose(_dl);
}

std::string const& ar::DLoader::getName() const
{
	return _name;
}

void ar::DLoader::setName(std::string const &name)
{
	_name = name;
}

void* ar::DLoader::sym(std::string const &symName)
{
	void *tmp = dlsym(_dl, symName.c_str());

	char *error(dlerror());
	if (error) {
		std::cerr << error << std::endl;
		throw std::runtime_error("Cannot access to symbol in lib :" + _name);
	}
	return tmp ? tmp : nullptr;
}