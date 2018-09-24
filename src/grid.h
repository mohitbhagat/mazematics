#ifndef GRID_H
#define GRID_H

#include "cell.h"
#include <iostream>
#include <memory>
#include <string>
#include <vector>

struct posn {
    int row;
    int col;
};

class Grid {
    std::vector<std::vector<Cell>> theGrid; // The actual grid.
    int width;
    int height;
    posn playerPosn;
    int pathLen = 1;
    int maxPathLen = 0;
    bool succeeded = false;
    bool failed = false;

    void applyToPathLen(char transformation);

public:
    Grid(int width, int height, std::string file = "");

    // To be used by graphical display, in order to render the grid in the
    // display
    std::vector<std::vector<Cell>>* getTheGrid();

    friend std::ostream& operator<<(std::ostream& out, const Grid& g);

    // Commands
    void right();
    void left();
    void up();
    void down();

    bool isSuccess();
    bool isFailure();

    int getPathLen() const;
    int getMaxPathLen() const;
};

#endif
