#ifndef CELL_H
#define CELL_H

#include <iostream>

const char player = 'O';
const char add = '+';
const char sub = '-';
const char mult = 'X';
const char sqr = '2';
const char cube = '3';
const char empty = '_';
const char goal = 'E';

class Cell {
	const int r;
	const int c;
	char type;

	public:
	Cell(int r, int c, char type);
	char getType() const;
	int getr() const;
	int getc() const;
	void setType(char newType);
};

#endif
