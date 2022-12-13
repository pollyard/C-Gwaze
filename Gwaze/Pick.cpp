#include "Pick.h"

// Constructor
Pick::Pick()
	:running(true)
	, mTicksCount(0)
	, tab(0)
{
}
// Destructor
Pick::~Pick()
{
	window.cleanUp();
	SDL_Quit();
	TTF_Quit();
}

// Public fuctions
void Pick::Loop()
{
	while (running) {
		_input();
		_update();
		window.render();
		// std::cout << window.mPos.x << " : " << window.mPos.y << " , " << window.mPos.state << std::endl;
	}
}
bool Pick::Init()
{
	// Initialize SDL
	int sdlResult = SDL_Init(SDL_INIT_VIDEO);
	if (sdlResult != 0) {
		SDL_Log("cannot initialize SDL: %s", SDL_GetError());
		return false;
	}

	// Initialize SDL_TTF
	int ttfResult = TTF_Init();
	if (ttfResult != 0) {
		SDL_Log("cannot initialize ttf: %s", TTF_GetError());
		return false;
	}

	// Initialize render class
	bool failed = window.Init();
	if (failed) {
		return false;
	}

	return true;
}

// Private functions
void Pick::_input()
{
	SDL_Event event;
	while (SDL_PollEvent(&event)) {
		if (SDL_QUIT == event.type) {
			running = false;
		}
		if (SDL_MOUSEMOTION == event.type) {
			SDL_GetMouseState(&window.mPos.x, &window.mPos.y);
		}
		if (SDL_MOUSEBUTTONDOWN == event.type) {
			if (SDL_BUTTON_LEFT == event.button.button) {
				std::cout << "Left Click" << std::endl;
				window.mPos.state = 1;
			}
			if (SDL_BUTTON_RIGHT == event.button.button) {
				std::cout << "Right Click" << std::endl;
				window.mPos.state = 2;
			}
		}
		if (event.type == SDL_KEYDOWN) {
			if (SDLK_0 == event.key.keysym.sym) {
				std::cout << "press 0" << std::endl;
				window.mPos.state = 3;
			}
			if (SDLK_ESCAPE == event.key.keysym.sym) {
				std::cout << "press escape" << std::endl;
				running = false;
			}
			if (SDLK_TAB == event.key.keysym.sym) {
				std::cout << "press tab" << std::endl;
				tab = 1;
			}
		}
	}
}
void Pick::_update()
{
	while (!SDL_TICKS_PASSED(SDL_GetTicks(), mTicksCount + 16));
	float deltaTime = (SDL_GetTicks() - mTicksCount) / 1000.0f;

	if (deltaTime > 0.05f) {
		deltaTime = 0.05f;
	}
	mTicksCount = SDL_GetTicks();

	if (window.mPos.state == 1) {
		if (window.mPos.x >= 0 && window.mPos.x <= width_quater - 1 && window.mPos.y <= 100) {
			window.stage = menu;
		}
		if (window.mPos.x >= width_quater + 1 && window.mPos.x <= width_half - 1 && window.mPos.y <= 100) {
			window.stage = predict;
		}
		if (window.mPos.x >= width_half + 1 && window.mPos.x <= width_threeQuater - 1 && window.mPos.y <= 100) {
			window.stage = result;
		}
		if (window.mPos.x >= width_threeQuater + 1 && window.mPos.x < width && window.mPos.y <= 100) {
			window.stage = hit;
		}
	}
	if (tab) {
		if (window.stage == menu) {
			window.stage = predict;
		}
		else if (window.stage == predict) {
			window.stage = result;
		}
		else if (window.stage == result) {
			window.stage = hit;
		}
		else if (window.stage == hit) {
			window.stage = menu;
		}
		tab = 0;
	}

	if (window.stage == menu) {

	}
	if (window.stage == predict) {
		for (int i = 1; i < 32; i++) {
			if (window.mPos.x >= window.pr[i].x && window.mPos.x <= window.pr[i].x + block_width
				&& window.mPos.y >= window.pr[i].y && window.mPos.y <= window.pr[i].y + block_height
				&& window.pr[i].texture != empty) {
				window.pr[i].state = 1;

				if (window.mPos.state == 1) {
					if (window.pr[(i / 2) * 2].texture != empty
						&& window.pr[(i / 2) * 2 + 1].texture != empty) {
						if (window.pr[i / 2].texture != empty) {
							for (int n = i / 2; n >= 1; n /= 2)
								window.pr[n].texture = empty;
						}
						window.pr[i / 2].texture = window.pr[i].texture;
					}
				}
			}
		}
		if (window.mPos.x >= (width / 2 - 90) && window.mPos.x <= (width / 2 + 90)
			&& window.mPos.y >= (height / 2 + 200) && window.mPos.y <= (height / 2 + 260)) {
			if (window.mPos.state == 1) {
				for (int i = 15; i >= 1; i--) {
					window.pr[i].texture = empty;
				}
			}
		}
	}
	if (window.stage == result) {
		if (window.mPos.x >= (width / 2 - 90) && window.mPos.x <= (width / 2 + 90)
			&& window.mPos.y >= (height / 2 + 200) && window.mPos.y <= (height / 2 + 260)) {
			if (window.mPos.state == 1) {
				for (int i = 15; i >= 1; i--) {
					if (window.pr[i].texture == empty) {
						window.count = 40;
						return;
					}
				}
				for (int i = 15; i >= 1; i--) {
					int temp = rand() % 2;

					if (temp) window.rs[i].texture = window.rs[i * 2].texture;
					else      window.rs[i].texture = window.rs[i * 2 + 1].texture;

					if (window.rs[i].texture == window.pr[i].texture) {
						window.rs[i].state = 1;
					}
					else if (window.rs[i].texture != window.pr[i].texture) {
						window.rs[i].state = 2;
					}
				}
			}
		}
	}
	if (window.stage == hit) {
		window.rate = 0;
		for (int i = 1; i <= 15; i++) {
			if (window.rs[i].state == 1) {
				window.rate++;
			}
		}
		window.rate = window.rate * 100 / 15;

		if (window.rate == 100) {
			window.hitRate[0] = '1';
			window.hitRate[1] = '0';
			window.hitRate[2] = '0';
			window.hitRate[3] = '%';
		}
		else if (window.rate >= 10) {
			window.hitRate[0] = (window.rate / 10) + '0';
			window.hitRate[1] = (window.rate % 10) + '0';
			window.hitRate[2] = '%';
		}
		else {
			window.hitRate[0] = window.rate + '0';
			window.hitRate[1] = '%';
		}
	}
	window.mPos.state = 0;

}