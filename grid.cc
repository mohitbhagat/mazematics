#include "grid.h"
#include <fstream>
using namespace std;

Grid::Grid(int width, int height, string file) : width{width}, height{height} {
	ifstream in{file};
	string line;
	getline(in, line);
	int row = 0;
	while (getline(in, line)) {
		int col = 0;
		theGrid.resize(row + 1);
		for (char &c : line) {
			theGrid.at(row).emplace_back(Cell(row, col, c));
			if (c == player) {
				playerPosn = {row, col};
			}
			col++;
		}
		row++;
	}
}

bool Grid::applyToPathLen(char transformation) {
	switch (transformation) {
		case empty:
			cout << "Empty:" << empty << "end" << endl;
			return true;
		case add:
			cout << "Add: " << add << endl;
			pathLen++;
			return true;
		case sub:
			cout << "Sub: " << sub << endl;
			pathLen--;
			return true;
		case mult:
			pathLen *= 2;
			return true;
		case sqr:
			pathLen = pathLen * pathLen;
			return true;
		case cube:
			pathLen = pathLen * pathLen * pathLen;
			return true;
		case goal:
			return false;
		default:
			return true;
	}
}

ostream &operator<<(std::ostream &out, const Grid &g) {
	out << "Len: " << g.pathLen << endl;
	out << ' ';
	for (int i = 0; i < g.width; i++) {
		out << '=';
	}
	out << endl;
	for (int i = 0; i < g.height; ++i) {
		out << '|';
		for (int j = 0; j < g.width; ++j) {
			out << g.theGrid.at(i).at(j).getType();
		}
		out << '|' << endl;
	}
	out << ' ';
	for (int i = 0; i < g.width; i++) {
		out << '=';
	}
	out << endl;
	return out;
}

bool Grid::right() {
	if (playerPosn.col >= width - 1) {
		return true;
	}
	theGrid.at(playerPosn.row).at(playerPosn.col).setType(empty);
	playerPosn.col += 1;
	bool ret = applyToPathLen(
	    theGrid.at(playerPosn.row).at(playerPosn.col).getType());
	theGrid.at(playerPosn.row).at(playerPosn.col).setType(player);
	return ret;
}

bool Grid::left() {
	if (playerPosn.col <= 0) {
		return true;
	}
	theGrid.at(playerPosn.row).at(playerPosn.col).setType(empty);
	playerPosn.col -= 1;
	bool ret = applyToPathLen(
	    theGrid.at(playerPosn.row).at(playerPosn.col).getType());
	theGrid.at(playerPosn.row).at(playerPosn.col).setType(player);
	return ret;
}

bool Grid::down() {
	if (playerPosn.row >= height - 1) {
		return true;
	}
	theGrid.at(playerPosn.row).at(playerPosn.col).setType(empty);
	playerPosn.row += 1;
	bool ret = applyToPathLen(
	    theGrid.at(playerPosn.row).at(playerPosn.col).getType());
	theGrid.at(playerPosn.row).at(playerPosn.col).setType(player);
	return ret;
}

bool Grid::up() {
	if (playerPosn.row <= 0) {
		return true;
	}
	theGrid.at(playerPosn.row).at(playerPosn.col).setType(empty);
	playerPosn.row -= 1;
	bool ret = applyToPathLen(
	    theGrid.at(playerPosn.row).at(playerPosn.col).getType());
	theGrid.at(playerPosn.row).at(playerPosn.col).setType(player);
	return ret;
}
