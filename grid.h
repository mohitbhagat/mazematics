#ifndef GRID_H
#define GRID_H

#include <iostream>
#include <memory>
#include <string>
#include <vector>
#include "cell.h"

struct posn {
	int row;
	int col;
};

class Grid {
	std::vector<std::vector<Cell>> theGrid;  // The actual grid.
	int width;
	int height;
	posn playerPosn;
	int pathLen = 1;

	bool applyToPathLen(char transformation);

       public:
	Grid(int width, int height, std::string file = "");

	friend std::ostream &operator<<(std::ostream &out, const Grid &g);

	// Commands
	bool right();
	bool left();
	bool up();
	bool down();
};

#endif
