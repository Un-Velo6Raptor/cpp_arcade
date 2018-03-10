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

	nibbler.displayMap();
	//nibbler.bigDisplay();
	
	do {
		std::cout << "> ";
		std::getline(std::cin, line);
		if (line == "up")
			nibbler.move(UP);
		else if (line == "down")
			nibbler.move(DOWN);
		else if (line == "left")
			nibbler.move(LEFT);
		else if (line == "right")
			nibbler.move(RIGHT);
		else if (line == "")
			nibbler.demo();
		nibbler.displayMap();
		//nibbler.bigDisplay();
	} while (line != "exit" && std::cin.eof() != 1);
	return 0;
}
