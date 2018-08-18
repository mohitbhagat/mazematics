#ifndef GRID_H
#define GRID_H

#include <iostream>
#include <memory>
#include <string>
#include <vector>
#include "cell.h"

class Grid {
	std::vector<std::vector<Cell>> theGrid;  // The actual grid.

       public:
	Grid(std::string file = "");

	friend std::ostream &operator<<(std::ostream &out, const Grid &g);
};

#endif
