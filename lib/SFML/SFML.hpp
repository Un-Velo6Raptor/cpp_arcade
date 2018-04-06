/*
** EPITECH PROJECT, 2021
** cpp_arcade
** File description:
** Created by sahel.lucas-saoudi@epitech.eu,
*/

#ifndef CPP_ARCADE_SFML_HPP
#define CPP_ARCADE_SFML_HPP

#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <IDisplay.hpp>

namespace ar {
	class SFML: public ar::IDisplay {
	public:
		SFML();
		~SFML() override = default;
		ar::Event getEvent(int &realEvent) override;
		bool canHandleSprites() override;
		void displayGame(const userInterface &UI, Map &map) override;
		void loadResources(const std::map<unsigned char, colorVector> &colors) override;
		void loadResources(const std::string &filePath, const std::map<unsigned char, spriteCoords> &sprites) override;
		void initMenu(const std::vector<std::string> &menuChoices, const std::string &menuName, const std::vector<std::string> &display) override;
		int refreshMenu(const ar::Event &key, const std::vector<userInterface> &dataArray) override;
		void refreshUsername(std::string &name, int realKey) override;
		void destroyMenu() override;

	private:
		sf::Texture _texture;
		std::map<unsigned char, sf::RectangleShape> _sprites;

		std::vector<std::string> _menuGamesName;
		std::vector<std::string> _menuGraphicalsLib;
		std::string _menuName;

		const unsigned int _windowWidth = 1920;
		const unsigned int _windowHeight = 1080;

		sf::RenderWindow *_window = nullptr;

		int _idx = 0;
	};
}

#endif //CPP_ARCADE_SFML_HPP
