#ifndef PUZZLES_H
#define PUZZLES_H

#include <string>
#include <vector>

class InvalidFileFormat {};

struct Puzzles {
	std::vector<std::string> thePuzzles;
	Puzzles(std::string stem);
};

#endif
