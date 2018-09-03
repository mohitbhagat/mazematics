#ifndef GAME_H
#define GAME_H

#include "grid.h"
#include "puzzles.h"
#include <memory>
#include <string>

class InvalidSaveFileFormat {
};
class UnableToWriteSaveFile {
};

class Game {
    int curLevel;
    bool gameFinished = false;
    bool succeeded = false;
    bool failed = false;
    Puzzles puzzles;
    std::string save;
    std::unique_ptr<Grid> g;
    void incLevel();

public:
    Game(std::string stem, std::string save);
    bool right();
    bool left();
    bool up();
    bool down();
    bool isGameFinished();
    bool isSuccess();
    bool isFailure();
    int getCurLevel() const;
    int getPathLen() const;
    int getMaxPathLen() const;
    void getPuzzle(int level);
    void nextPuzzle();
    std::vector<std::vector<Cell>>* getTheGrid();
    void retry();

    friend std::ostream& operator<<(std::ostream& out, const Game& gm);
};

#endif
