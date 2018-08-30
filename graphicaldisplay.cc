#include "graphicaldisplay.h"
#include "cell.h"
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
				renderer = SDL_CreateRenderer(
				    window, -1, SDL_RENDERER_ACCELERATED);
				if (renderer == nullptr) {
					cout
					    << "renderer could not be created! "
					       "SDL_Error: "
					    << SDL_GetError() << endl;
				}
			}
		}
	}
	return success;
}

SDL_Texture *loadTexture(SDL_Renderer *renderer, string file) {
	SDL_Texture *texture = nullptr;
	SDL_Surface *loaded = nullptr;

	loaded = IMG_Load(file.c_str());
	if (loaded == nullptr) {
		cout << "Error loading image! IMG_Error: " << file << " "
		     << IMG_GetError() << endl;
	} else {
		texture = SDL_CreateTextureFromSurface(renderer, loaded);
		if (texture == nullptr) {
			cout << "Error creating texture! IMG_Error: " << file
			     << " " << IMG_GetError() << endl;
		}
		SDL_FreeSurface(loaded);
	}
	return texture;
}

bool GraphicalDisplay::loadMedia() {
	bool success = true;
	textures["add"] = loadTexture(renderer, "./pics/add.bmp");
	if (textures["add"] == NULL) {
		cout << "Unable to load ./pics/add.bmp" << endl;
	}
	textures["sub"] = loadTexture(renderer, "./pics/sub.bmp");
	if (textures["sub"] == NULL) {
		cout << "Unable to load ./pics/sub.bmp" << endl;
	}
	textures["mult"] = loadTexture(renderer, "./pics/mult.bmp");
	if (textures["mult"] == NULL) {
		cout << "Unable to load ./pics/mult.bmp" << endl;
	}
	textures["sqr"] = loadTexture(renderer, "./pics/sqr.bmp");
	if (textures["sqr"] == NULL) {
		cout << "Unable to load ./pics/sqr.bmp" << endl;
	}
	textures["cube"] = loadTexture(renderer, "./pics/cube.bmp");
	if (textures["cube"] == NULL) {
		cout << "Unable to load ./pics/cube.bmp" << endl;
	}
	textures["goal"] = loadTexture(renderer, "./pics/goal.bmp");
	if (textures["goal"] == NULL) {
		cout << "Unable to load ./pics/goal.bmp" << endl;
	}
	return success;
}

void GraphicalDisplay::closeDisplay() {
	SDL_DestroyWindow(window);
	window = nullptr;

	map<string, SDL_Texture *>::iterator it = textures.begin();
	while (it != textures.end()) {
		SDL_DestroyTexture(it->second);
	}

	IMG_Quit();
	SDL_Quit();
}

void drawGrid(SDL_Renderer *renderer, shared_ptr<vector<vector<Cell>>> theGrid,
	      map<string, SDL_Texture *> &textures) {
	const int paddingTop = 70;
	const int paddingLeft = 70;
	const int cellWidth = 50;
	const int cellHeight = 50;
	const int cellMargin = 50;
	for (int i = 0; i < theGrid->size(); i++) {
		for (int j = 0; j < theGrid->at(i).size(); j++) {
			Cell cur = theGrid->at(i).at(j);
			char type = cur.getType();
			SDL_Rect rect = {paddingLeft + cur.getc() * cellWidth,
					 paddingTop + cur.getr() * cellHeight,
					 cellWidth, cellHeight};
			switch (type) {
				case player:
					SDL_SetRenderDrawColor(renderer, 0, 255,
							       0, 255);
					SDL_RenderFillRect(renderer, &rect);
					break;
				case add:
					SDL_RenderCopy(renderer,
						       textures["add"], nullptr,
						       &rect);
					break;
				case sub:
					SDL_RenderCopy(renderer,
						       textures["sub"], nullptr,
						       &rect);
					break;
				case mult:
					SDL_RenderCopy(renderer,
						       textures["mult"],
						       nullptr, &rect);
					break;
				case sqr:
					SDL_RenderCopy(renderer,
						       textures["sqr"], nullptr,
						       &rect);
					break;
				case cube:
					SDL_RenderCopy(renderer,
						       textures["cube"],
						       nullptr, &rect);
					break;
				case empty:
					SDL_SetRenderDrawColor(renderer, 255,
							       255, 255, 255);
					SDL_RenderFillRect(renderer, &rect);
					break;
				case goal:
					SDL_RenderCopy(renderer,
						       textures["goal"],
						       nullptr, &rect);
					break;
			}
		}
	}
}

void GraphicalDisplay::draw() {
	SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
	SDL_RenderClear(renderer);
	drawGrid(renderer, theGrid, textures);
	SDL_RenderPresent(renderer);
}
