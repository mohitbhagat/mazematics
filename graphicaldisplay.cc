#include "graphicaldisplay.h"
using namespace std;

GraphicalDisplay::GraphicalDisplay(string size, Game &gm)
    : theGrid{shared_ptr<vector<vector<Cell>>>(gm.getTheGrid())} {
	if (size == "large") {
		this->width = lrgWidth;
		this->height = lrgHeight;
	}
}

bool GraphicalDisplay::initDisplay() {
	bool success = true;

	if (SDL_Init(SDL_INIT_VIDEO) < 0) {
		cout << "SDL could not initialize! SDL_ERROR: "
		     << SDL_GetError() << endl;
		success = false;
	} else {
		window = SDL_CreateWindow("Maze", SDL_WINDOWPOS_UNDEFINED,
					  SDL_WINDOWPOS_UNDEFINED, width,
					  height, SDL_WINDOW_SHOWN);

		if (window == NULL) {
			cout << "window could not be created! SDL_ERROR: "
			     << SDL_GetError() << endl;
			success = false;
		} else {
			screenSurface = SDL_GetWindowSurface(window);
			this->renderer = SDL_CreateRenderer(
			    window, -1, SDL_RENDERER_ACCELERATED);
			if (renderer == nullptr) {
				cout << "renderer could not be created! "
					"SDL_Error: "
				     << SDL_GetError() << endl;
			} else {
				if (SDL_SetRenderDrawColor(renderer, 255, 255,
							   255, 255)) {
					cout << "SDL_SetRenderDrawColor "
						"failed! Error: "
					     << SDL_GetError() << endl;
				}
			}
		}
	}
	return success;
}

void GraphicalDisplay::closeDisplay() {
	SDL_FreeSurface(screenSurface);
	screenSurface = NULL;

	SDL_DestroyWindow(window);
	window = NULL;

	SDL_Quit();
}

bool drawGrid(SDL_Window *window, SDL_Surface *screenSurface,
	      SDL_Renderer *renderer) {
	bool success = true;
	SDL_Rect rect = {50, 50, 50, 50};
	SDL_RenderClear(renderer);
	SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
	success = !SDL_RenderFillRect(renderer, &rect);
	return success;
}

bool GraphicalDisplay::draw() {
	bool success = true;
	success = drawGrid(window, screenSurface, renderer);
	SDL_RenderPresent(renderer);

	return success;
}
