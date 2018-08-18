#include "game.h"
#include <fstream>
using namespace std;

Game::Game(string stem, string save) : puzzles{Puzzles(stem)}, save{save} {
	ifstream in(save);
	if (!(in >> curLevel)) {
		throw InvalidSaveFileFormat{};
	}
	g = Grid(puzzles.thePuzzles.at(curLevel));
}

void Game::incLevel() {
	ofstream out(save);
	curLevel++;
	if (!(out << curLevel)) {
		throw UnableToWriteSaveFile{};
	}
}

ostream &operator<<(std::ostream &out, const Game &gm) {
	out << gm.g;
	return out;
}
