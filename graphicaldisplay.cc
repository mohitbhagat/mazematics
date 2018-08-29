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

		if (window == nullptr) {
			cout << "window could not be created! SDL_ERROR: "
			     << SDL_GetError() << endl;
			success = false;
		} else {
			int imgFlags = IMG_INIT_PNG;
			if (!(IMG_Init(imgFlags) && imgFlags)) {
				cout << "IMG could not be initialized! Error: "
				     << IMG_GetError() << endl;
			} else {
				screenSurface = SDL_GetWindowSurface(window);
				SDL_SetColorKey(screenSurface, SDL_TRUE, 1);
				this->renderer = SDL_CreateRenderer(
				    window, -1, SDL_RENDERER_ACCELERATED);
				if (renderer == nullptr) {
					cout
					    << "renderer could not be created! "
					       "SDL_Error: "
					    << SDL_GetError() << endl;
				} else {
					if (SDL_SetRenderDrawColor(
						renderer, 255, 255, 255, 255)) {
						cout
						    << "SDL_SetRenderDrawColor "
						       "failed! Error: "
						    << SDL_GetError() << endl;
					}
				}
			}
		}
	}
	return success;
}

SDL_Texture *loadSurfaceToTexture(SDL_Renderer *renderer,
				  SDL_Surface *screenSurface, string path) {
	SDL_Surface *surface = nullptr;
	SDL_Texture *ret = nullptr;
	surface = SDL_LoadBMP(path.c_str());
	if (surface == nullptr) {
		cout << "Unable to load surface '" << path
		     << "' Error: " << SDL_GetError() << endl;
	} else {
		ret = SDL_CreateTextureFromSurface(renderer, surface);
		if (surface) {
			SDL_FreeSurface(surface);
		}
		if (ret == nullptr) {
			cout << "SDL_CreateTextureFromSurface failed! "
				"Error: "
			     << SDL_GetError() << endl;
		}
	}
	return ret;
}

bool GraphicalDisplay::loadMedia() {
	bool success = true;
	SDL_Texture *add = nullptr;
	add = loadSurfaceToTexture(renderer, screenSurface, "./pics/add.bmp");
	textures.insert(pair<string, SDL_Texture *>("add", add));
	return success;
}

void GraphicalDisplay::closeDisplay() {
	SDL_FreeSurface(screenSurface);
	screenSurface = NULL;

	SDL_DestroyWindow(window);
	window = NULL;

	map<string, SDL_Texture *>::iterator it = textures.begin();
	while (it != textures.end()) {
		SDL_DestroyTexture(it->second);
	}

	IMG_Quit();
	SDL_Quit();
}

bool drawGrid(SDL_Window *window, SDL_Surface *screenSurface,
	      SDL_Renderer *renderer) {
	bool success = true;
	SDL_Rect rect = {50, 50, 500, 500};
	SDL_Rect outline = {53, 53, 494, 494};
	SDL_RenderClear(renderer);
	SDL_SetRenderDrawColor(renderer, 0, 0, 255, 255);
	success = !SDL_RenderFillRect(renderer, &rect);
	SDL_SetRenderDrawColor(renderer, 255, 255, 0, 255);
	success = !SDL_RenderFillRect(renderer, &outline);
	return success;
}

bool GraphicalDisplay::draw() {
	bool success = true;
	success = drawGrid(window, screenSurface, renderer);
	SDL_RenderPresent(renderer);
	SDL_Rect textureArea = {50, 50, 64, 64};
	SDL_RenderCopy(renderer, textures["add"], NULL, &textureArea);
	cout << "SDL_RenderCopy Error: " << SDL_GetError() << endl;
	return success;
}
