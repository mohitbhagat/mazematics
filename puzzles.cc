#include "puzzles.h"
#include <fstream>
using namespace std;

bool checkFileFormat(std::string file) {
	ifstream in{file};
	string line;
	getline(in, line);
	if (!getline(in, line)) {
		return false;
	}
	int len = line.length();
	while (getline(in, line)) {
		if (line.length() != len) {
			return false;
		}
	}
	return true;
}

int Puzzles::getWidthAtLevel(int i) {
	ifstream in{thePuzzles.at(i)};
	string line;
	getline(in, line);
	if (!getline(in, line)) {
		string s = "Puzzle file empty";
		throw s;
	}
	return line.length();
}

int Puzzles::getHeightAtLevel(int i) {
	ifstream in{thePuzzles.at(i)};
	string line;
	int height = 0;
	getline(in, line);
	while (getline(in, line)) {
		height++;
	}
	return height;
}

Puzzles::Puzzles(std::string stem) {
	ifstream in{stem};
	string file;
	while (in >> file) {
		if (checkFileFormat(file)) {
			thePuzzles.emplace_back(file);
		} else {
			throw InvalidFileFormat{};
		}
	}
}
