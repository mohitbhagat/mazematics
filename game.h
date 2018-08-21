#ifndef GAME_H
#define GAME_H

#include <memory>
#include <string>
#include "grid.h"
#include "puzzles.h"

class InvalidSaveFileFormat {};
class UnableToWriteSaveFile {};

class Game {
	int curLevel;
	bool gameFinished = false;
	bool succeeded = false;
	bool failed = false;
	Puzzles puzzles;
	std::string save;
	std::unique_ptr<Grid> g;
	void incLevel();

       public:
	Game(std::string stem, std::string save);
	bool right();
	bool left();
	bool up();
	bool down();
	bool isGameFinished();
	bool isSuccess();
	int getCurLevel() const;
	void getPuzzle(int level);
	void nextPuzzle();
	void endGame();

	friend std::ostream &operator<<(std::ostream &out, const Game &gm);
};

#endif
