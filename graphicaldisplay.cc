#include "graphicaldisplay.h"
using namespace std;

GraphicalDisplay::GraphicalDisplay(string size, Game& gm)
    : theGrid{shared_ptr<vector<vector<Cell>>>(gm.getTheGrid())} {
	if (size == "large") {
		this->width = lrgWidth;
		this->height = lrgHeight;
	}
}

bool GraphicalDisplay::initDisplay() {
	bool success = true;

	if (SDL_Init(SDL_INIT_VIDEO) < 0) {
		cerr << "SDL could not initialize! SDL_ERROR: "
		     << SDL_GetError() << endl;
		success = false;
	} else {
		Window = SDL_CreateWindow("Maze", SDL_WINDOWPOS_UNDEFINED,
					  SDL_WINDOWPOS_UNDEFINED, width,
					  height, SDL_WINDOW_SHOWN);

		if (Window == NULL) {
			cout << "Window could not be created! SDL_ERROR: "
			     << SDL_GetError() << endl;
			success = false;
		} else {
			ScreenSurface = SDL_GetWindowSurface(Window);
			Renderer = SDL_CreateRenderer(Window, -1,
						      SDL_RENDERER_ACCELERATED);
		}
	}
	return success;
}

void GraphicalDisplay::closeDisplay() {
	SDL_FreeSurface(ScreenSurface);
	ScreenSurface = NULL;

	SDL_DestroyWindow(Window);
	Window = NULL;

	SDL_Quit();
}

bool GraphicalDisplay::update() {
	bool success = true;

	return success;
}
