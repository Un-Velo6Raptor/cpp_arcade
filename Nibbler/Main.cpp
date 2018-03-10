//
// EPITECH PROJECT, 2018
// Arcade
// File description:
// test main for Nibbler
//

#include	<iostream>
#include	"Nibbler.hpp"

int		main()
{
	Nibbler	nibbler;
	std::string     line;
	int             input;

	while (line != "exit" && std::cin.eof() != 1 && nibbler.move() != false) {
		nibbler.displayMap();
		//nibbler.bigDisplay();
		std::cout << "> ";
		std::getline(std::cin, line);
		if (line == "up")
			nibbler.setDirection(UP);
		else if (line == "down")
			nibbler.setDirection(DOWN);
		else if (line == "left")
			nibbler.setDirection(LEFT);
		else if (line == "right")
			nibbler.setDirection(RIGHT);
		else if (line == "")
			nibbler.demo();
	}
	nibbler.displayMap();
	//nibbler.bigDisplay();	
	return 0;
}
