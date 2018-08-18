#include <fstream>
#include <iostream>
#include <string>
#include "game.h"

int main(int argc, char* argv[]) {
	if (argc != 3) {
		std::cout << "Invalid number of arguments. Please provide 2 "
			     "arguments."
			  << std::endl;
		return 1;
	}
	std::string stemArg(argv[1]);
	std::string saveArg(argv[2]);
	Game gm = Game(stemArg, saveArg);
	std::cout << gm;

	return 0;
}
