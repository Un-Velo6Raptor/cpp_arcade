/*
** EPITECH PROJECT, 2018
** cpp_arcade
** File description:
** Created by martin.januario@epitech.eu,
*/

#ifndef CPP_ARCADE_SDL2_HPP
# define CPP_ARCADE_SDL2_HPP

# include <string>
# include <SDL2/SDL.h>
# include <SDL2/SDL_image.h>
# include <SDL2/SDL_ttf.h>
# include "IDisplay.hpp"

namespace ar {

	class SDL2 : public ar::IDisplay {
	public:
		SDL2();
		~SDL2() override;

		ar::Event getEvent(int &) override;
		bool canHandleSprites() override;
		void displayGame(const userInterface &, ar::Map &) override;
		void loadResources(const std::map<unsigned char, colorVector> &) override;
		void loadResources(const std::string &, const std::map<unsigned char, spriteCoords> &) override;

		void initMenu(const std::vector<std::string> &, const std::string &, const std::vector<std::string> &) override;
		int refreshMenu(const ar::Event &, const std::vector<userInterface> &) override;
		void refreshUsername(std::string &, int) override;
		void destroyMenu() override;

	private:
		SDL_Window *_window;
		SDL_Renderer *_renderer;

		unsigned int _windowWidth = 1920;
		unsigned int _windowHeight = 1080;

		unsigned int _index = 0;
		std::string _username = "Unknown";
		std::string _menuName;
		std::vector<std::string> _gameName;
		std::vector<std::string> _graphicalName;

		SDL_Texture *_texture;
		std::map<unsigned char, ar::spriteCoords> _sprites;

	};
}

#endif //CPP_ARCADE_SDL2_HPP
