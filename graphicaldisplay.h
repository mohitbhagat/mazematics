#ifndef GRAPHICALDISPLAY_H
#define GRAPHICALDISPLAY_H

#include <SDL2/SDL.h>
#include "game.h"

const int medWidth = 800;
const int medHeight = 600;
const int lrgWidth = 1024;
const int lrgHeight = 768;

class GraphicalDisplay {
	int width = medWidth;
	int height = medHeight;
	SDL_Window *window = nullptr;
	SDL_Surface *screenSurface = nullptr;
	SDL_Renderer *renderer = nullptr;
	std::shared_ptr<std::vector<std::vector<Cell>>> theGrid = nullptr;

       public:
	GraphicalDisplay(std::string size, Game &gm);
	bool initDisplay();
	bool loadMedia();
	bool draw();
	void closeDisplay();
};

#endif
