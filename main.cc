#include "game.h"
#include "graphicaldisplay.h"
#include <fstream>
#include <iostream>
#include <string>

//#if defined(unix) || defined(__unix__) || defined(__unix)
//#define PREDEF_PLATFORM_UNIX
#include <SDL2/SDL.h>
//#endif

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
	bool help = false;
	gd->clearScreen();
	gd->drawGrid();
	gd->renderPresent();
	while (!quit) {
		SDL_Event e;
		cout << "Game Loop" << endl;
		while (SDL_WaitEvent(&e) != 0) {
			SDL_FlushEvent(SDL_MOUSEMOTION);
			if (e.type == SDL_QUIT) {
				quit = true;
				break;
			}
			if (e.type == SDL_KEYUP) {
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
					case SDLK_h:
						help = true;
						break;
					default:
						break;
				}
			}
			gd->clearScreen();
			gd->drawGrid();
			gd->renderPresent();
			if (gm->isSuccess() || gm->isFailure() || gm->isGameFinished() || quit || help) {
				break;
			}
		}

		if (help) {
			gd->clearScreen();
			gd->drawHelpScreen();
			gd->renderPresent();
			while (SDL_WaitEvent(&e) != 0) {
				SDL_FlushEvent(SDL_MOUSEMOTION);
				bool close = false;
				gd->clearScreen();
				gd->drawHelpScreen();
				gd->renderPresent();
				if (e.type == SDL_QUIT) {
					gd->closeDisplay();
					quit = true;
					break;
				} else if (e.type == SDL_KEYUP) {
					switch (e.key.keysym.sym) {
						case SDLK_h:
							close = true;
							break;
						case SDLK_q:
							quit = true;
							break;
						default:
							break;
					}
					if (close) {
						help = false;
						break;
					}
					if (quit) {
						break;
					}
				}
			}
		}

		if (gm->isSuccess()) {
			gd->clearScreen();
			gd->drawSuccessScreen();
			gd->renderPresent();
			while (SDL_WaitEvent(&e) != 0) {
				SDL_FlushEvent(SDL_MOUSEMOTION);
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
						case SDLK_RIGHT:
							nextEntered = true;
							break;
						case SDLK_q:
							quit = true;
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
				if (quit) {
					break;
				}
			}
		}
		if (gm->isFailure()) {
			gd->clearScreen();
			gd->drawFailureScreen();
			gd->renderPresent();
			while (SDL_WaitEvent(&e) != 0) {
				SDL_FlushEvent(SDL_MOUSEMOTION);
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
						case SDLK_LEFT:
							retryEntered = true;
							break;
						case SDLK_q:
							quit = true;
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
				if (quit) {
					break;
				}
			}
		}
		if (gm->isGameFinished()) {
			gd->clearScreen();
			gd->drawGameOver();
			gd->renderPresent();
			while (SDL_WaitEvent(&e) != 0) {
				SDL_FlushEvent(SDL_MOUSEMOTION);
				gd->clearScreen();
				gd->drawGameOver();
				gd->renderPresent();
				if (e.type == SDL_QUIT) {
					gd->closeDisplay();
					quit = true;
					break;
				} else if (e.type == SDL_KEYUP) {
					switch (e.key.keysym.sym) {
						case SDLK_q:
							quit = true;
							break;
						default:
							break;
					}
				}
				if (quit) {
					break;
				}
			}
			break;
		}
		gd->clearScreen();
		gd->drawGrid();
		gd->renderPresent();
		SDL_Delay(100);
	}
	gd->closeDisplay();
	return 0;
}
