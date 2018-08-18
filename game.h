#ifndef GAME_H
#define GAME_H

#include <string>
#include "grid.h"
#include "puzzles.h"

class InvalidSaveFileFormat {};
class UnableToWriteSaveFile {};

class Game {
	int curLevel;
	Puzzles puzzles;
	std::string save;
	Grid g;
	void incLevel();

       public:
	Game(std::string stem, std::string save);

	friend std::ostream &operator<<(std::ostream &out, const Game &gm);
};

#endif
