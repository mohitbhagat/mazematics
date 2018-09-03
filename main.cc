#include "game.h"
#include "graphicaldisplay.h"
#include <SDL2/SDL.h>
#include <fstream>
#include <iostream>
#include <string>
using namespace std;

const string stemFile = "stem.txt";
const string saveFile = "save.txt";

int main(int argc, char* args[])
{
    shared_ptr<Game> gm = make_shared<Game>(stemFile, saveFile);
    gm->getPuzzle(gm->getCurLevel());
    unique_ptr<GraphicalDisplay> gd = make_unique<GraphicalDisplay>("medium", gm);
    gd->initDisplay();
    gd->loadMedia();

    bool quit = false;
    SDL_Event e;
    while (SDL_WaitEvent(&e) != 0) {
	cout << "outer loop" << endl;
	gd->clearScreen();
	gd->drawGrid();
	gd->renderPresent();
	if (e.type == SDL_QUIT) {
	    quit = true;
	} else if (e.type == SDL_KEYUP) {
	    cout << "Key up" << endl;
	    switch (e.key.keysym.sym) {
	    case SDLK_UP:
		gm->up();
		break;
	    case SDLK_DOWN:
		gm->down();
		break;
	    case SDLK_RIGHT:
		gm->right();
		break;
	    case SDLK_LEFT:
		gm->left();
		break;
	    case SDLK_q:
		quit = true;
		break;
	    default:
		break;
	    }
	}

	if (gm->isSuccess()) {
	    gd->clearScreen();
	    gd->drawSuccessScreen();
	    gd->renderPresent();
	    while (SDL_WaitEvent(&e) != 0) {
		cout << "Success Loop" << endl;
		bool nextEntered = false;
		gd->clearScreen();
		gd->drawSuccessScreen();
		gd->renderPresent();
		if (e.type == SDL_QUIT) {
		    gd->closeDisplay();
		    quit = true;
		    break;
		} else if (e.type == SDL_KEYUP) {
		    switch (e.key.keysym.sym) {
		    case SDLK_n:
			nextEntered = true;
			break;
		    case SDLK_q:
			quit = false;
			break;
		    default:
			break;
		    }
		}
		if (nextEntered) {
		    gm->nextPuzzle();
		    cout << gm << endl;
		    break;
		}
	    }
	}
	if (gm->isFailure()) {
	    gd->clearScreen();
	    gd->drawFailureScreen();
	    gd->renderPresent();
	    while (SDL_WaitEvent(&e) != 0) {
		cout << "Failure Loop" << endl;
		bool retryEntered = false;
		gd->clearScreen();
		gd->drawFailureScreen();
		gd->renderPresent();
		if (e.type == SDL_QUIT) {
		    gd->closeDisplay();
		    quit = true;
		    break;
		} else if (e.type == SDL_KEYUP) {
		    switch (e.key.keysym.sym) {
		    case SDLK_r:
			retryEntered = true;
			break;
		    case SDLK_q:
			quit = false;
			break;
		    default:
			break;
		    }
		}
		if (retryEntered) {
		    gm->retry();
		    cout << gm << endl;
		    break;
		}
	    }
	}
	if (gm->isGameFinished()) {
	    gd->clearScreen();
	    gd->drawGameOver();
	    gd->renderPresent();
	    while (SDL_WaitEvent(&e) != 0) {
		cout << "Failure Loop" << endl;
		bool gameOverEntered = false;
		gd->clearScreen();
		gd->drawGameOver();
		gd->renderPresent();
		if (e.type == SDL_QUIT) {
		    gd->closeDisplay();
		    quit = true;
		    break;
		} else if (e.type == SDL_KEYUP) {
		    switch (e.key.keysym.sym) {
		    case SDLK_r:
			gameOverEntered = true;
			break;
		    case SDLK_q:
			quit = false;
			break;
		    default:
			break;
		    }
		}
		if (gameOverEntered) {
		    break;
		}
	    }
	    break;
	}
	gd->clearScreen();
	gd->drawGrid();
	gd->renderPresent();
	if (quit) {
	    break;
	}
    }
    gd->closeDisplay();
    return 0;
}
