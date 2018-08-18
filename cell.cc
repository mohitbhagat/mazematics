#include "cell.h"
using namespace std;

Cell::Cell(int r, int c, char type) : r{r}, c{c}, type{type} {};

char Cell::getType() const { return type; }
