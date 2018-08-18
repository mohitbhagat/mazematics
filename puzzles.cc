#include "puzzles.h"
#include <fstream>
using namespace std;

bool checkFileFormat(std::string file) {
	ifstream in{file};
	string line;
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
