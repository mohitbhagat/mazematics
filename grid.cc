#include "grid.h"
#include <fstream>
#include <sstream>
using namespace std;

Grid::Grid(int width, int height, string file) : width{width}, height{height} {
	ifstream in{file};
	string line;
	getline(in, line);
	stringstream putToInt(line);
	putToInt >> maxPathLen;
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

void Grid::applyToPathLen(char transformation) {
	switch (transformation) {
		case empty:
			cout << "Empty:" << empty << "end" << endl;
			break;
		case add:
			cout << "Add: " << add << endl;
			pathLen++;
			break;
		case sub:
			cout << "Sub: " << sub << endl;
			pathLen--;
			break;
		case mult:
			pathLen *= 2;
			break;
		case sqr:
			pathLen = pathLen * pathLen;
			break;
		case cube:
			pathLen = pathLen * pathLen * pathLen;
			break;
		case goal:
			if (pathLen > maxPathLen) {
				failed = true;
				break;
			}
			succeeded = true;
			break;
		default:
			return;
	}
}

ostream &operator<<(std::ostream &out, const Grid &g) {
	out << "Max: " << g.maxPathLen << endl;
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

void Grid::right() {
	if (playerPosn.col >= width - 1) {
		return;
	}
	theGrid.at(playerPosn.row).at(playerPosn.col).setType(empty);
	playerPosn.col += 1;
	applyToPathLen(theGrid.at(playerPosn.row).at(playerPosn.col).getType());
	theGrid.at(playerPosn.row).at(playerPosn.col).setType(player);
	return;
}

void Grid::left() {
	if (playerPosn.col <= 0) {
		return;
	}
	theGrid.at(playerPosn.row).at(playerPosn.col).setType(empty);
	playerPosn.col -= 1;
	applyToPathLen(theGrid.at(playerPosn.row).at(playerPosn.col).getType());
	theGrid.at(playerPosn.row).at(playerPosn.col).setType(player);
	return;
}

void Grid::down() {
	if (playerPosn.row >= height - 1) {
		return;
	}
	theGrid.at(playerPosn.row).at(playerPosn.col).setType(empty);
	playerPosn.row += 1;
	applyToPathLen(theGrid.at(playerPosn.row).at(playerPosn.col).getType());
	theGrid.at(playerPosn.row).at(playerPosn.col).setType(player);
	return;
}

void Grid::up() {
	if (playerPosn.row <= 0) {
		return;
	}
	theGrid.at(playerPosn.row).at(playerPosn.col).setType(empty);
	playerPosn.row -= 1;
	applyToPathLen(theGrid.at(playerPosn.row).at(playerPosn.col).getType());
	theGrid.at(playerPosn.row).at(playerPosn.col).setType(player);
	return;
}

bool Grid::isSuccess() { return succeeded; }

bool Grid::isFailure() { return failed; }
