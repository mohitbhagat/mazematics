#include "graphicaldisplay.h"
#include "cell.h"
using namespace std;

GraphicalDisplay::GraphicalDisplay(string size, shared_ptr<Game> gm)
    : gm{ gm }
{
    if (size == "large") {
	this->width = lrgWidth;
	this->height = lrgHeight;
    }
}

bool GraphicalDisplay::initDisplay()
{
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
		} else {
		    if (TTF_Init() == -1) {
			cout << "Failed to initialize SDL_ttf! Error: " << SDL_GetError() << endl;
		    }
		}
	    }
	}
    }
    return success;
}

SDL_Texture* loadTexture(SDL_Renderer* renderer, string file)
{
    SDL_Texture* texture = nullptr;
    SDL_Surface* loaded = nullptr;

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

bool GraphicalDisplay::loadMedia()
{
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

void GraphicalDisplay::closeDisplay()
{
    SDL_DestroyWindow(window);
    window = nullptr;
    SDL_DestroyRenderer(renderer);
    renderer = nullptr;

    map<string, SDL_Texture*>::iterator it = textures.begin();
    for (it = textures.begin(); it != textures.end(); it++) {
	SDL_DestroyTexture(it->second);
    }
    IMG_Quit();
    SDL_Quit();
}

void drawMessage(SDL_Renderer* renderer, string message, string font, int size, SDL_Color color, SDL_Rect* messageRect)
{
    const char* cFont = font.c_str();
    TTF_Font* textFont = TTF_OpenFont(cFont, size);
    const char* cMessage = message.c_str();
    SDL_Surface* surfaceMessage = TTF_RenderText_Solid(textFont, cMessage, color);
    SDL_Texture* theMessage = SDL_CreateTextureFromSurface(renderer, surfaceMessage);
    SDL_RenderCopy(renderer, theMessage, NULL, messageRect);

    SDL_DestroyTexture(theMessage);
    SDL_FreeSurface(surfaceMessage);
    TTF_CloseFont(textFont);
}

void GraphicalDisplay::drawGrid()
{
    vector<vector<Cell>>* theGrid = gm->getTheGrid();
    if (theGrid == nullptr) {
	return;
    }
    const int cellWidth = 60;
    const int cellHeight = 60;
    const int borderWidth = 5;
    const int sidePanelWidth = 250;
    const int gridHeight = medHeight - borderWidth * 2;
    const int gridWidth = medWidth - sidePanelWidth - borderWidth * 2;
    const int puzzleHeight = theGrid->size() * cellHeight;
    const int puzzleWidth = theGrid->at(0).size() * cellWidth;
    const int paddingTop = (gridHeight - puzzleHeight) / 2;
    const int paddingLeft = (gridWidth - puzzleWidth) / 2;

    SDL_Rect rect = { 0, 0, 800, 500 };
    SDL_Texture* texture = loadTexture(renderer, "./pics/grid.bmp");
    SDL_RenderCopy(renderer, texture, nullptr, &rect);

    SDL_Texture* playerTexture = loadTexture(renderer, "./pics/player.bmp");

    int row = theGrid->size();
    for (int i = 0; i < row; i++) {
	int col = theGrid->at(i).size();
	for (int j = 0; j < col; j++) {
	    Cell cur = theGrid->at(i).at(j);
	    char type = cur.getType();
	    SDL_Rect rect = { paddingLeft + cur.getc() * cellWidth,
		paddingTop + cur.getr() * cellHeight,
		cellWidth, cellHeight };
	    switch (type) {
	    case player:
		SDL_RenderCopy(renderer, playerTexture, nullptr, &rect);
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
	    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
	    SDL_RenderDrawRect(renderer, &rect);
	}
    }

    //Print the game text containers
    SDL_Rect border = { medWidth - 235, 82, 100, 50 };
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
    SDL_RenderFillRect(renderer, &border);
    border.y += 92;
    SDL_RenderFillRect(renderer, &border);

    //Print the game text
    SDL_Rect messageRect = { medWidth - 220, 75, 10, 60 };
    SDL_Color color = { 0, 0, 0, 255 };
    string text = to_string(gm->getPathLen());
    messageRect.w = 25 * text.length();
    drawMessage(renderer, text, "./fonts/OpenSans-Regular.ttf", 500, color, &messageRect);
    text = to_string(gm->getMaxPathLen());
    messageRect.y += 92;
    messageRect.w = 25 * text.length();
    drawMessage(renderer, text, "./fonts/OpenSans-Regular.ttf", 500, color, &messageRect);
}

void GraphicalDisplay::drawSuccessScreen()
{
    SDL_Rect rect = { 0, 0, 800, 500 };
    SDL_Texture* texture = loadTexture(renderer, "./pics/success.bmp");
    SDL_RenderCopy(renderer, texture, nullptr, &rect);
}

void GraphicalDisplay::drawFailureScreen()
{
    SDL_Rect rect = { 0, 0, 800, 500 };
    SDL_Texture* texture = loadTexture(renderer, "./pics/failure.bmp");
    SDL_RenderCopy(renderer, texture, nullptr, &rect);
}

void GraphicalDisplay::drawHelpScreen()
{
    SDL_Rect rect = { 0, 0, 800, 500 };
    SDL_Texture* texture = loadTexture(renderer, "./pics/help.bmp");
    SDL_RenderCopy(renderer, texture, nullptr, &rect);
}

void GraphicalDisplay::drawGameOver()
{
    SDL_Rect rect = { 0, 0, 800, 500 };
    SDL_Texture* texture = loadTexture(renderer, "./pics/gameover.bmp");
    SDL_RenderCopy(renderer, texture, nullptr, &rect);
}

void GraphicalDisplay::drawMenu()
{
    SDL_Color color = { 0, 0, 0, 255 };
    SDL_Rect messageRect = { 50, 50, 100, 100 };
    drawMessage(renderer, "Menu", "./fonts/OpenSans-Regular.ttf", 500, color, &messageRect);
}

void GraphicalDisplay::clearScreen()
{
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
    SDL_RenderClear(renderer);
}

void GraphicalDisplay::renderPresent()
{
    SDL_RenderPresent(renderer);
}
