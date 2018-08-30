#include <SDL2/SDL.h>
#include <fstream>
#include <iostream>
#include <string>
#include "game.h"
#include "graphicaldisplay.h"
using namespace std;

int main(int argc, char* args[]) {
	bool graphics = false;

	if (argc != 3 && argc != 4) {
		cout << "Invalid number of arguments. Please provide 2 or 3"
			" arguments."
		     << endl;
		return 1;
	}
	string stemArg(args[1]);
	string saveArg(args[2]);
	Game gm = Game(stemArg, saveArg);
	gm.getPuzzle(gm.getCurLevel());

	if (argc == 4) {
		graphics = true;
		if (strcmp(args[3], "large") != 0 &&
		    strcmp(args[3], "medium") != 0) {
			cout << "Please enter 'medium' or 'large' for the "
				"screen size"
			     << endl;
			return 1;
		}
	}

	unique_ptr<GraphicalDisplay> gd = nullptr;

	if (graphics) {
		gd.reset(new GraphicalDisplay(args[3], gm));
		gd->initDisplay();
		gd->loadMedia();
	}

	string input;
	while (1) {
		if (gm.isSuccess()) {
			cout << "Congratulations! You completed the "
				"puzzle"
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

		if (gd) {
			bool quit = false;
			gd->draw();
			SDL_Event e;
			while (SDL_PollEvent(&e) != 0) {
				if (e.type == SDL_QUIT) {
					cout << "The Program has been closed"
					     << endl;
					quit = true;
				}
			}
			if (quit) {
				gd->closeDisplay();
				gd.reset();
			}
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
	gd->closeDisplay();
	return 0;
}
