#pragma once
#include "Render.h"

class Pick {
public:
	// Constructor & Destructor
	Pick();
	virtual ~Pick();

	// Public functions
	void Loop(void);
	bool Init(void);

private:
	// System functions
	void _input(void);
	void _update(void);

	// System variables
	bool         running;
	Uint32       mTicksCount;
	RenderWindow window;

	// functions

	// variables
	int tab;

	// Color Variables
	SDL_Color white = { 255, 255, 255 , 255 };
	SDL_Color black = { 0,   0,   0   , 255 };

};