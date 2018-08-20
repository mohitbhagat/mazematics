#include "game.h"
#include <fstream>
using namespace std;

Game::Game(string stem, string save)
    : puzzles{Puzzles(stem)}, save{save}, g{nullptr} {
	ifstream in(save);
	if (!(in >> curLevel)) {
		throw InvalidSaveFileFormat{};
	}
}

int Game::getCurLevel() const { return curLevel; }

void Game::getPuzzle(int level) {
	if (level >= puzzles.thePuzzles.size()) {
		gameFinished = true;
		return;
	}
	g.reset(new Grid(puzzles.getWidthAtLevel(curLevel),
			 puzzles.getHeightAtLevel(curLevel),
			 puzzles.thePuzzles.at(curLevel)));
}

void Game::incLevel() {
	ofstream out(save);
	curLevel++;
	if (!(out << curLevel)) {
		throw UnableToWriteSaveFile{};
	}
}

ostream &operator<<(std::ostream &out, const Game &gm) {
	out << *(gm.g);
	return out;
}

bool Game::right() {
	bool finished = !(g->right());
	if (finished) {
		curLevel++;
		getPuzzle(curLevel);
	}
}

bool Game::left() {
	bool finished = !(g->left());
	if (finished) {
		curLevel++;
		getPuzzle(curLevel);
	}
}

bool Game::up() {
	bool finished = !(g->up());
	if (finished) {
		curLevel++;
		getPuzzle(curLevel);
	}
}

bool Game::down() {
	bool finished = !(g->down());
	if (finished) {
		curLevel++;
		getPuzzle(curLevel);
	}
}

bool Game::isGameFinished() { return gameFinished; }
