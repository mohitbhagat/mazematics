#include <fstream>
#include <iostream>
#include <string>
#include "game.h"
using namespace std;

int main(int argc, char* argv[]) {
	if (argc != 3) {
		cout << "Invalid number of arguments. Please provide 2 "
			"arguments."
		     << endl;
		return 1;
	}
	string stemArg(argv[1]);
	string saveArg(argv[2]);
	Game gm = Game(stemArg, saveArg);
	gm.getPuzzle(gm.getCurLevel());

	string input;
	while (1) {
		if (gm.isSuccess()) {
			cout << "Congratulations! You completed the puzzle"
			     << endl;
			cout << "Enter n to go to the next puzzle" << endl;
			cin >> input;
			if (cin.fail() || cin.eof()) {
				break;
			}
			if (input == "n") {
				gm.nextPuzzle();
			}
		}
		if (gm.isFailure()) {
			cout << "Failed, enter rt to retry" << endl;
			cin >> input;
			if (cin.fail() || cin.eof()) {
				break;
			}
			if (input == "rt") {
				gm.retry();
			}
		}
		if (gm.isGameFinished()) {
			cout << "Game Finished!" << endl;
			break;
		}

		cout << gm;
		cin >> input;
		if (cin.fail() || cin.eof()) {
			break;
		}
		if (input == "r") {
			gm.right();
		} else if (input == "l") {
			gm.left();
		} else if (input == "u") {
			gm.up();
		} else if (input == "d") {
			gm.down();
		}
	}

	return 0;
}
