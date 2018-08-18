#include "grid.h"
#include <fstream>
using namespace std;

Grid::Grid(string file) {
	ifstream in{file};
	string line;
	int row = 0;
	while (getline(in, line)) {
		int col = 0;
		theGrid.resize(row + 1);
		for (char &c : line) {
			theGrid.at(row).emplace_back(Cell(row, col, c));
			col++;
		}
		row++;
	}
}

ostream &operator<<(std::ostream &out, const Grid &g) {
	for (int i = 0; i < g.theGrid.size(); ++i) {
		for (int j = 0; j < g.theGrid.at(i).size(); ++j) {
			out << g.theGrid.at(i).at(j).getType();
		}
		out << endl;
	}
	return out;
}
