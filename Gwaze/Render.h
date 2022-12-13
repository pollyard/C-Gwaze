#pragma once
#include <iostream>
#include <string>
#include <Windows.h>
#include <ctime>
#include "SDL.h"
#include "SDL_ttf.h"
#include "SDL_image.h"

#define width        1024
#define height       768
#define wall_thick   1
#define block_width  60
#define block_height 40
#define empty        nullptr

#define width_zero        0
#define width_quater      width / 4
#define width_half        width / 2
#define width_threeQuater width / 2 + width / 4

#define Nederlanden 1
#define USA         2
#define Argentina   3
#define Australia   4
#define Japan       5
#define Croatia     6
#define Brazil      7
#define Korea       8
#define France      9
#define Poland      10
#define England     11
#define Senegal     12
#define Morocco     13
#define Spain       14
#define Portuguese  15
#define Swiss       16

struct Mouse {
	int x;
	int y;
	int state;
};
enum Stage {
	menu = 1,
	predict,
	result,
	hit,
	glgl
};
struct Country {
	SDL_Texture* texture;
	int x;
	int y;
	int state;
};

class RenderWindow 
{
public:
	// Constructor & Destructor
	RenderWindow();
	virtual ~RenderWindow();

	// Delete functions
	void cleanUp();
	void render();

	// Functions
	bool Init();

	// Variables
	Mouse   mPos;
	Stage   stage;
	Country pr[32];
	Country rs[32];
	int     count;
	int     rate;
	char    hitRate[5];
	int     push;

private:
	// Functions
	void _RenderFlags();
	void _drawTexture(SDL_Texture* texture, float x, float y);
	SDL_Texture* _loadTexture(const char* filePath);
	void _writeText(float x, float y, const char* text, SDL_Color color, TTF_Font* font);
	void _drawHeader();
	void _drawMenu();
	void _drawPredict();
	void _drawResult();
	void _drawHit();
	void _drawBack();

	// Variavle
	SDL_Window*   window;
	SDL_Renderer* renderer;
	TTF_Font*     font12;
	TTF_Font*     font34;
	TTF_Font*     font80;
	TTF_Font*     font132;

	// Color variable
	SDL_Color white  = { 244, 244, 244, 255 };
	SDL_Color black  = {  35,  31,  32, 255 };
	SDL_Color purple = {  89,  73, 227, 255 };
	SDL_Color green  = { 128, 255,   0, 255 };
	SDL_Color red    = { 235,   0,   0, 255 };
	SDL_Color gray   = {  74,  74,  74, 255 };

	// flags
	SDL_Texture* Nederlanden_flag;
	SDL_Texture* USA_flag;
	SDL_Texture* Argentina_flag;
	SDL_Texture* Australia_flag;
	SDL_Texture* Japan_flag;
	SDL_Texture* Croatia_flag;
	SDL_Texture* Brazil_flag;
	SDL_Texture* Korea_flag;
	SDL_Texture* France_flag;
	SDL_Texture* Poland_flag;
	SDL_Texture* England_flag;
	SDL_Texture* Senegal_flag;
	SDL_Texture* Morocco_flag;
	SDL_Texture* Spain_flag;
	SDL_Texture* Portuguese_flag;
	SDL_Texture* Swiss_flag;
};