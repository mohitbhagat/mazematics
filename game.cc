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
	g->right();
	if (g->isSuccess()) {
		succeeded = true;
	}
	if (g->isFailure()) {
		failed = true;
	}
}

bool Game::left() {
	g->left();
	if (g->isSuccess()) {
		succeeded = true;
	}
	if (g->isFailure()) {
		failed = true;
	}
}

bool Game::up() {
	g->up();
	if (g->isSuccess()) {
		succeeded = true;
	}
	if (g->isFailure()) {
		failed = true;
	}
}

bool Game::down() {
	g->down();
	if (g->isSuccess()) {
		succeeded = true;
	}
	if (g->isFailure()) {
		failed = true;
	}
}

bool Game::isGameFinished() { return gameFinished; }

bool Game::isSuccess() { return succeeded; }

bool Game::isFailure() { return failed; }

void Game::nextPuzzle() {
	curLevel++;
	succeeded = false;
	getPuzzle(curLevel);
}

void Game::retry() {
	failed = false;
	getPuzzle(curLevel);
}
