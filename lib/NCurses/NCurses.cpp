//
// EPITECH PROJECT, 2018
// Arcade
// File description:
// nCurses class
//

#include	<utility>
#include	<vector>
#include	<algorithm>
#include	<curses.h>
#include	"NCurses.hpp"

ar::NCurses::NCurses() : _selectedGame(0), _username("")
{
	initscr();
	cbreak();
	noecho();
	keypad(stdscr, true);
	curs_set(false);
	timeout(0);
	start_color();
	init_pair(1, COLOR_WHITE, COLOR_BLACK);
	init_pair(2, COLOR_BLACK, COLOR_WHITE);
	init_pair(3, COLOR_RED, COLOR_RED);
	init_pair(4, COLOR_GREEN, COLOR_GREEN);
	init_pair(5, COLOR_YELLOW, COLOR_YELLOW);
	init_pair(6, COLOR_BLUE, COLOR_BLUE);
	init_pair(7, COLOR_MAGENTA, COLOR_MAGENTA);
	init_pair(8, COLOR_CYAN, COLOR_CYAN);
	init_pair(9, COLOR_GREEN, COLOR_BLACK);
}

ar::NCurses::~NCurses()
{
	endwin();
}

ar::Event	ar::NCurses::getEvent(int &realEvent)
{
	std::map<int, ar::Event>	keyBinding = {
		{ KEY_UP, ar::AR_UP },
		{ KEY_DOWN, ar::AR_DOWN },
		{ KEY_LEFT, ar::AR_LEFT },
		{ KEY_RIGHT, ar::AR_RIGHT },
		{ '1', ar::AR_PREV_GAME },
		{ '2', ar::AR_NEXT_GAME },
		{ '3', ar::AR_PREV_GRAPH_LIB },
		{ '4', ar::AR_NEXT_GRAPH_LIB },
		{ 'm', ar::AR_MENU },
		{ 'p', ar::AR_PAUSE },
		{ ' ', ar::AR_ACTION },
		{ 'r', ar::AR_RESTART },
		{ 27, ar::AR_EXIT },
		{ 10, ar::AR_VALIDATE }
	};
	std::map<int, ar::Event>::iterator it;

	realEvent = getch();
	it = keyBinding.find(realEvent);
	if (it != keyBinding.end())
		return keyBinding.find(realEvent)->second;
	return ar::AR_UNKNOWN;
}

bool		ar::NCurses::canHandleSprites()
{
	return false;
}

int		ar::NCurses::findColorPair(int value)
{
	std::map<unsigned char, ar::colorVector>::iterator	it;

	it = _colorLegend.find(value);
	if (it == _colorLegend.end())
		return 1;
	if (it->second.red > it->second.green * 2 && it->second.red > it->second.blue * 2)
		return 3;
	if (it->second.green > it->second.red * 2 && it->second.green > it->second.blue * 2)
		return 4;
	if (it->second.blue * 2 < it->second.green && it->second.blue * 2 < it->second.red)
		return 5;
	if (it->second.blue > it->second.green * 2 && it->second.blue > it->second.red * 2)
		return 6;
	if (it->second.green * 2 < it->second.red && it->second.green * 2 < it->second.blue)
		return 7;
	if (it->second.red * 2 < it->second.green && it->second.red * 2 < it->second.blue)
		return 8;
	if (it->second.red + it->second.green + it->second.blue > 383)
		return 2;
	return 1;
}

int		ar::NCurses::getMul(int width, int height, ar::Map &map)
{
	if (width > map.getWidth() * 4 && height > map.getHeight() * 2 + 1)
		return 4;
	if (width > map.getWidth() * 2 && height > map.getHeight() + 1)
		return 2;
	return 1;
}

int		ar::NCurses::getStartY(int width, int height, ar::Map &map)
{
	if (width > map.getWidth() * 4 && height > map.getHeight() * 2 + 1)
		return height / 2 - map.getHeight();
	return height / 2 - map.getHeight() / 2;
}

int		ar::NCurses::getStartX(int width, int height, ar::Map &map)
{
	if (width > map.getWidth() * 4 && height > map.getHeight() * 2 + 1)
		return width / 2 - map.getWidth() * 2;
	if (width > map.getWidth() * 2 && height > map.getHeight() + 1)
		return width / 2 - map.getWidth();
	return width / 2 - map.getWidth() / 2;
}

void		ar::NCurses::displayMap(ar::Map &map, const int mul, const std::pair<int, int> start)
{
	std::string	str(mul, ' ');

	for (int y = 0 ; y < map.getHeight() ; y++) {
		for (int x = 0 ; x < map.getWidth() ; x++) {
			attron(COLOR_PAIR(findColorPair(map[y][x])));
			mvprintw(start.first + y * ((mul + 1) / 2),
				 start.second + x * mul, str.c_str());
			if (mul == 4)
				mvprintw(start.first + y * ((mul + 1) / 2) + 1,
					 start.second + x * mul, str.c_str());
			attron(COLOR_PAIR(1));
		}
	}
}

void		ar::NCurses::displayGame(const ar::userInterface &UI, ar::Map &map)
{
	std::string	score = "Score: " + std::to_string(UI.score);
	std::string	time = "Time: " + std::to_string(UI.time);
	int	height;
	int	width;
	getmaxyx(stdscr, height, width);
	int	mul = getMul(width, height, map);
	std::pair<int, int>	start;

	start.first = getStartY(width, height, map) + 1;
	start.second = getStartX(width, height, map);
	erase();
	if (height < map.getHeight() + 2 || width < map.getWidth()) {
		mvprintw(height / 2, width / 2 - 9, "Resize your window");
	} else {
		mvprintw(start.first - 2, start.second, UI.username.c_str());
		mvprintw(start.first - 2, start.second + map.getWidth() * mul - 9, time.c_str());
		mvprintw(start.first - 1, start.second, score.c_str());
		displayMap(map, mul, start);
	}
	refresh();
}

void		ar::NCurses::loadResources(const std::map<unsigned char, ar::colorVector> &color)
{
	_colorLegend = color;
}

void		ar::NCurses::loadResources(const __attribute__ ((unused)) std::string &filePath,
					const __attribute__ ((unused)) std::map<unsigned char,
					ar::spriteCoords> &sprites)
{
}

void		ar::NCurses::initMenu(const std::vector<std::string> &menuChoices,
				  const std::string &menuName, const std::vector<std::string> &display)
{
	erase();
	_menuChoices = { "Snake", "Qix", "Nibbler", "Qix", "Exit" };
	_menuName = menuName;
	_display = display;
}

void		ar::NCurses::displayName(const int width) const
{
	const std::map<int, std::string>	name = {
		{ 1, "        **                                                **              " },
		{ 2, "     *****                                                 **             " },
		{ 3, "    *  ***                                                 **             " },
		{ 4, "       ***                                                 **             " },
		{ 5, "      *  **       ***  ****                                **             " },
		{ 6, "      *  **        **** **** *    ****       ****      *** **      ***    " },
		{ 7, "     *    **        **   ****    * ***  *   * ***  *  *********   * ***   " },
		{ 8, "     *    **        **          *   ****   *   ****  **   ****   *   ***  " },
		{ 9, "    *      **       **         **         **    **   **    **   **    *** " },
		{ 10, "    *********       **         **         **    **   **    **   ********  " },
		{ 11, "   *        **      **         **         **    **   **    **   *******   " },
		{ 12, "   *        **      **         **         **    **   **    **   **        " },
		{ 13, "  *****      **     ***        ***     *  **    **   **    **   ****    * " },
		{ 14, " *   ****    ** *    ***        *******    ***** **   *****      *******  " },
		{ 15, "*     **      **                 *****      ***   **   ***        *****   " },
		{ 16, "*                                                                         " },
		{ 17, " **                                                                       " }
	};

	attron(COLOR_PAIR(9));
	std::for_each(name.begin(), name.end(), [width](std::pair<int, std::string> str)
		      { mvprintw(str.first, width / 2 - str.second.size() / 2, str.second.c_str()); }
		);
	attron(COLOR_PAIR(1));
}

void		ar::NCurses::printGameName(int &i, const int width, const std::string str) const
{
	if (i - 19 == _selectedGame)
		attron(COLOR_PAIR(2));
	mvprintw(i, width / 2 - str.size() / 2, str.c_str());
	if (i - 19 == _selectedGame)
		attron(COLOR_PAIR(1));
	i++;
}

void		ar::NCurses::printHighScore(const int width, const ar::userInterface ui) const
{
	std::string	highscore = "High Score: " + ui.username + " "
		+ std::to_string(ui.score) + " " + std::to_string(ui.time);
	mvprintw(17, width / 2 - highscore.size() / 2, highscore.c_str());
}

void		ar::NCurses::printLibName(int &i, const int width, const std::string str) const
{
	std::size_t found = str.find_last_of("/");

	mvprintw(i, width - (str.substr(found + 1).size() + 1), str.substr(found + 1).c_str());
	i--;
}

int		ar::NCurses::refreshMenu(const ar::Event &key,
				     const std::vector<ar::userInterface> &dataArray)
{
	int	gameSize = dataArray.size();
	int	libSize = _display.size();
	int	height;
	int	width;
	int	i = 19;

	getmaxyx(stdscr, height, width);
	erase();
	if (key == ar::AR_UP && _selectedGame > 0)
		_selectedGame--;
	if (key == ar::AR_DOWN && _selectedGame < gameSize - 1)
		_selectedGame++;
	if (gameSize + libSize + 18 < height && width > 74) {
		displayName(width);
		std::for_each(_menuChoices.begin(), _menuChoices.end(),
			      [&i, width, this](std::string str){ printGameName(i, width, str); }
			);
		printHighScore(width, dataArray.at(_selectedGame));
		i = height - 1;
		std::for_each(_display.begin(), _display.end(), [&i, width, this](std::string str)
			      { printLibName(i, width, str); }
			);
		mvprintw(1, width / 2 - 10, "Choose your username:");
		mvprintw(3, width / 2 - _username.size() / 2, _username.c_str());
	} else {
		mvprintw(height / 2, width / 2 - 9, "Resize your window");
	}
	refresh();
	return _selectedGame;
}

void		ar::NCurses::refreshUsername(std::string &name, int realKey)
{
	if ((realKey == 127 || realKey == KEY_BACKSPACE) && name.size() > 0)
		name.pop_back();
	else if (name.size() < 12 && ((realKey >= 'a' && realKey <= 'z') ||
				      (realKey >= 'A' && realKey <= 'Z')))
		name.append(1, realKey);
	_username = name;
}

void		ar::NCurses::destroyMenu()
{
	erase();
}

extern "C" ar::NCurses *createDisplay()
{
	return new ar::NCurses();
}

extern "C" void destroyDisplay(ar::NCurses *ncurses)
{
	delete ncurses;
}
