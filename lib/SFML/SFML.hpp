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
#include "IDisplay.hpp"

namespace ar {
	class SFML: public ar::IDisplay {
	public:
		SFML();
		~SFML() override;
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

		void displayScore(int score, int boxSizeX, int boxSizeY);
		void displayUsername(std::string const &username, int boxSizeX, int boxSizeY);
		void displayTime(int time, int boxSizeX, int boxSizeY);
		void displayUserInterface(ar::userInterface const &user);

		void menuDisplayGames();
		void menuDisplayGraphicals();
		void menuDisplayUsername();
		void menuDisplayTitle();
		void menuManageKey(ar::Event const &key, std::vector<ar::userInterface> const &datas);

		sf::Texture _texture;
		std::map<unsigned char, sf::RectangleShape> _sprites;
		sf::Font _font;

		std::vector<std::string> _menuGamesName;
		std::vector<std::string> _menuGraphicalsLib;
		std::string _menuName;

		/**
		 * Internal Menu Configuration
		 */
		const std::string _backgroundPath = "resources/un_seul_etre_vous_manque_et_tout_est_depeuple_SFML_background.png";
		const std::string _titleFontPath = "resources/font/Arcade Classic.ttf";
		sf::Font _titleFont;
		sf::Texture _menuBackground;

		/**
		 * Internal UserInterface Configuration
		 */
		 const unsigned int _userHeight = 100;
		 const unsigned int _userMarginTop = 10;
		 const unsigned int _userMarginLeft = 100;
		 const unsigned int _userMarginRight = 100;
		 const unsigned int _userMarginBottom = 10;

		/**
		 * Internal Window Configuration
		 */
		int _windowWidth = 1920;
		int _windowHeight = 1080;
		const std::string _fontPath = "resources/font/Zenzai Itacha.ttf";
		const unsigned int _fontSize = 40;

		/**
		 * Internal Game Configuration
		 */
		const unsigned int _gameMarginTop = 60;
		const unsigned int _gameMarginLeft = 60;
		const unsigned int _gameMarginRight = 60;
		const unsigned int _gameMarginBottom = 20;

		/**
		 * transcription of sf::Event (type = KeyPressed) in ar::Event
		 */
		 std::map<std::pair<bool, int>, ar::Event> _events = {
			{{true, sf::Keyboard::Num1}, ar::Event::AR_PREV_GAME},
			{{true, sf::Keyboard::Num2}, ar::Event::AR_NEXT_GAME},
			{{true, sf::Keyboard::Num3}, ar::Event::AR_PREV_GRAPH_LIB},
			{{true, sf::Keyboard::Quote}, ar::Event::AR_NEXT_GRAPH_LIB},
			{{false, sf::Keyboard::R}, ar::Event::AR_RESTART},
			{{false, sf::Keyboard::P}, ar::Event::AR_PAUSE},
			{{false, sf::Keyboard::M}, ar::Event::AR_MENU},
			{{false, sf::Keyboard::Space}, ar::Event::AR_ACTION},
			{{false, sf::Keyboard::Up}, ar::Event::AR_UP},
			{{false, sf::Keyboard::Left}, ar::Event::AR_LEFT},
			{{false, sf::Keyboard::Right}, ar::Event::AR_RIGHT},
			{{false, sf::Keyboard::Down}, ar::Event::AR_DOWN},
			{{false, sf::Keyboard::Escape}, ar::Event::AR_EXIT},
			{{false, sf::Keyboard::Return}, ar::Event::AR_VALIDATE}
		 };


		sf::RenderWindow *_window = nullptr;
		std::string _username;

		int _idx = 0;
	};
}

#endif //CPP_ARCADE_SFML_HPP
