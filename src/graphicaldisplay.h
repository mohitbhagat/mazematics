#ifndef GRAPHICALDISPLAY_H
#define GRAPHICALDISPLAY_H

#include "game.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <map>
#include <string>

const int medWidth = 800;
const int medHeight = 500;
const int lrgWidth = 1024;
const int lrgHeight = 768;

class GraphicalDisplay {
	int width = medWidth;
	int height = medHeight;
	SDL_Window* window = nullptr;
	SDL_Renderer* renderer = nullptr;
	std::shared_ptr<Game> gm = nullptr;
	std::map<std::string, SDL_Texture*> textures;

	public:
	GraphicalDisplay(std::string size, std::shared_ptr<Game> gm);
	bool initDisplay();
	bool loadMedia();
	void drawGrid();
	void drawSuccessScreen();
	void drawFailureScreen();
	void drawHelpScreen();
	void drawGameOver();
	void drawMenu();
	void clearScreen();
	void renderPresent();
	void closeDisplay();
};

#endif
