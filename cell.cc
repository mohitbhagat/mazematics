#include "cell.h"
using namespace std;

Cell::Cell(int r, int c, char type) : r{r}, c{c}, type{type} {};

char Cell::getType() const { return type; }

int Cell::getr() const { return r; }

int Cell::getc() const { return c; }

void Cell::setType(char newType) { type = newType; }
