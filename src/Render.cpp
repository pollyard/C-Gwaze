#include "Render.h"

// Constructor & Destructor
RenderWindow::RenderWindow()
	:window(nullptr)
	,renderer(nullptr)
	,stage(menu)
	,mPos({ 0, 0, 0 })
	// initialize flag
	,Nederlanden_flag(empty)
	,USA_flag(empty)
	,Argentina_flag(empty)
	,Australia_flag(empty)
	,Japan_flag(empty)
	,Croatia_flag(empty)
	,Brazil_flag(empty)
	,Korea_flag(empty)
	,France_flag(empty)
	,Poland_flag(empty)
	,England_flag(empty)
	,Senegal_flag(empty)
	,Morocco_flag(empty)
	,Spain_flag(empty)
	,Portuguese_flag(empty)
	,Swiss_flag(empty)
	,count(0)
	,font12(empty)
	,font34(empty)
	,font80(empty)
	,font132(empty)
	,rate(0.f)
	,hitRate()
	,push(0)
{
	// Create SDL window
	window = SDL_CreateWindow(
		"PICK EM",
		100,
		100,
		width,
		height,
		0
	);
	if (!window) {
		SDL_Log("failed to create window: %s", SDL_GetError());
	}

	// Create SDL renderer
	renderer = SDL_CreateRenderer(
		window,
		-1,
		SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC
	);
	if (!renderer) {
		SDL_Log("failed to create renderer: %s", SDL_GetError());
	}
	
	Nederlanden_flag = _loadTexture("flag/Nederlanden.png");
	USA_flag         = _loadTexture("flag/USA.png");
	Argentina_flag   = _loadTexture("flag/Argentina.png");
	Australia_flag   = _loadTexture("flag/Australia.png");
	Japan_flag       = _loadTexture("flag/Japan.png");
	Croatia_flag     = _loadTexture("flag/Croatia.png");
	Brazil_flag      = _loadTexture("flag/Brazil.png");
	Korea_flag       = _loadTexture("flag/Korea.png");
	France_flag      = _loadTexture("flag/France.png");
	Poland_flag      = _loadTexture("flag/Poland.png");
	England_flag     = _loadTexture("flag/England.png");
	Senegal_flag     = _loadTexture("flag/Senegal.png");
	Morocco_flag     = _loadTexture("flag/Morocco.png");
	Spain_flag       = _loadTexture("flag/Spain.png");
	Portuguese_flag  = _loadTexture("flag/Portuguese.png");
	Swiss_flag       = _loadTexture("flag/Swiss.png");
	
	for (int i = 0; i < 32; i++) {
		pr[i].x       = 0;
		pr[i].y       = 0;
		pr[i].state   = 0;
		pr[i].texture = empty;
	}
	pr[16].texture = Nederlanden_flag;
	pr[17].texture = USA_flag;
	pr[18].texture = Argentina_flag;
	pr[19].texture = Australia_flag;
	pr[20].texture = Japan_flag;
	pr[21].texture = Croatia_flag;
	pr[22].texture = Brazil_flag;
	pr[23].texture = Korea_flag;
	pr[24].texture = England_flag;
	pr[25].texture = Senegal_flag;
	pr[26].texture = France_flag;
	pr[27].texture = Poland_flag;
	pr[28].texture = Morocco_flag;
	pr[29].texture = Spain_flag;
	pr[30].texture = Portuguese_flag;
	pr[31].texture = Swiss_flag;
	pr[1].x  = 478, pr[1].y  = 317;
	pr[2].x  = 389, pr[2].y  = 407;
	pr[3].x  = 567, pr[3].y  = 407;
	pr[4].x  = 288, pr[4].y  = 283;
	pr[5].x  = 288, pr[5].y  = 522;
	pr[6].x  = 658, pr[6].y  = 283;
	pr[7].x  = 658, pr[7].y  = 522;
	pr[8].x  = 165, pr[8].y  = 229;
	pr[9].x  = 165, pr[9].y  = 344;
	pr[10].x = 165, pr[10].y = 466;
	pr[11].x = 165, pr[11].y = 585;
	pr[12].x = 786, pr[12].y = 229;
	pr[13].x = 786, pr[13].y = 344;
	pr[14].x = 786, pr[14].y = 466;
	pr[15].x = 786, pr[15].y = 585;
	pr[16].x =  50, pr[16].y = 203;
	pr[17].x =  50, pr[17].y = 251;
	pr[18].x =  50, pr[18].y = 323;
	pr[19].x =  50, pr[19].y = 371;
	pr[20].x =  50, pr[20].y = 443;
	pr[21].x =  50, pr[21].y = 491;
	pr[22].x =  50, pr[22].y = 563;
	pr[23].x =  50, pr[23].y = 611;
	pr[24].x = 909, pr[24].y = 203;
	pr[25].x = 909, pr[25].y = 251;
	pr[26].x = 909, pr[26].y = 323;
	pr[27].x = 909, pr[27].y = 371;
	pr[28].x = 909, pr[28].y = 443;
	pr[29].x = 909, pr[29].y = 491;
	pr[30].x = 909, pr[30].y = 563;
	pr[31].x = 909, pr[31].y = 611;

	for (int i = 1; i < 32; i++) {
		rs[i].x       = pr[i].x;
		rs[i].y       = pr[i].y;
		rs[i].state   = pr[i].state;
		rs[i].texture = empty;
	
		if(i >= 16) {
			rs[i].texture = pr[i].texture;
		}
	}

}
RenderWindow::~RenderWindow() 
{

}

// Delete functions
void RenderWindow::cleanUp() 
{
	SDL_DestroyWindow(window);
	SDL_DestroyRenderer(renderer);
}

bool RenderWindow::Init()
{
	// Open font
	font12 = TTF_OpenFont("./LINESeedKR-Rg.ttf", 12);
	if (font12 == NULL) {
		std::cout << "cannot read font file" << std::endl;
		return true;
	}
	font34 = TTF_OpenFont("./LINESeedKR-Rg.ttf", 34);
	if (font34 == NULL) {
		std::cout << "cannot read font file" << std::endl;
		return true;
	}
	font80 = TTF_OpenFont("./LINESeedKR-Rg.ttf", 80);
	if (font80 == NULL) {
		std::cout << "cannot read font file" << std::endl;
		return true;
	}
	font132 = TTF_OpenFont("./LINESeedKR-Rg.ttf", 132);
	if (font132 == NULL) {
		std::cout << "cannot read font file" << std::endl;
		return true;
	}
	return false;
}

SDL_Texture* RenderWindow::_loadTexture(const char* filePath) 
{
	SDL_Texture* texture = NULL;
	texture = IMG_LoadTexture(renderer, filePath);
	if (texture == NULL)
		std::cout << "failed to load texture. Error: " << SDL_GetError() << std::endl;
	return texture;
}

// Render Functions
void RenderWindow::render() 
{
	SDL_SetRenderDrawColor(renderer, white.r, white.g, white.b, white.a);
	SDL_RenderClear(renderer);

	if (stage == menu) {
		_drawMenu();
		_drawHeader();
	}
	else if (stage == predict) {
		_drawPredict();
		_drawHeader();
	}
	else if (stage == result) {
		_drawResult();
		_drawHeader();
	}
	else if (stage == hit) {
		_drawHit();
		_drawHeader();
	}

	SDL_RenderPresent(renderer);
}
void RenderWindow::_writeText(float x, float y, const char* text, SDL_Color color, TTF_Font* font) 
{
	SDL_Surface* SFmessage = TTF_RenderText_Solid(font, text, color);
	SDL_Texture* message   = SDL_CreateTextureFromSurface(renderer, SFmessage);
	if (SFmessage == nullptr) {
		printf("cannot create surface");
		exit(-1);
	}
	if (message == nullptr) {
		printf("cannot create surface");
		exit(-1);
	}
	SDL_Rect src;
	src.x = 0;
	src.y = 0;
	src.w = SFmessage->w;
	src.h = SFmessage->h;

	SDL_Rect dst;
	dst.x = x - (src.w / 2);
	dst.y = y - (src.h / 2);
	dst.w = src.w;
	dst.h = src.h;

	SDL_RenderCopy(renderer, message, &src, &dst);
	SDL_FreeSurface(SFmessage);
	SDL_DestroyTexture(message);
}
void RenderWindow::_drawHeader() 
{
	// draw background
	SDL_SetRenderDrawColor(renderer, black.r, black.g, black.b, black.a);
	SDL_Rect wall{ 0, 0, width, 100 };
	SDL_RenderFillRect(renderer, &wall);

	SDL_SetRenderDrawColor(renderer, purple.r, purple.g, purple.b, purple.a);
	if (mPos.x >= width_zero && mPos.x <= width_quater - 1 && mPos.y <= 100) {
		wall = { 0, 0, width_quater, 100 };
		SDL_RenderFillRect(renderer, &wall);
	}
	if (mPos.x >= width_quater + 1 && mPos.x <= width_half - 1 && mPos.y <= 100) {
		wall = { width_quater + 1, 0, width_quater - 1, 100 };
		SDL_RenderFillRect(renderer, &wall);
	}
	if (mPos.x >= width_half + 1 && mPos.x <= width_threeQuater - 1 && mPos.y <= 100) {
		wall = { width_half + 1, 0, width_quater - 1, 100 };
		SDL_RenderFillRect(renderer, &wall);
	}
	if (mPos.x >= width_threeQuater + 1 && mPos.x < width && mPos.y <= 100) {
		wall = { width_threeQuater + 1, 0, width_quater - 1, 100 };
		SDL_RenderFillRect(renderer, &wall);
	}

	// draw text
	_writeText(width_quater / 2, 50, "menu"    , white, font34);
	_writeText(width_half - (width_quater / 2), 50, "predict", white, font34);
	_writeText(width_half + (width_quater / 2), 50, "result"  , white, font34);
	_writeText(width_threeQuater + (width_quater / 2), 50, "hit rate", white, font34);

	// draw wall
	SDL_SetRenderDrawColor(renderer, white.r, white.g, white.b, white.a);
	wall = { width / 4, 10, wall_thick, 70 };
	SDL_RenderFillRect(renderer, &wall);
	wall.x = width / 2;
	SDL_RenderFillRect(renderer, &wall);
	wall.x = width / 2 + width / 4;
	SDL_RenderFillRect(renderer, &wall);
	//std::cout << "render" << std::endl;

}
void RenderWindow::_drawMenu() 
{
	SDL_SetRenderDrawColor(renderer, white.r, white.g, white.b, white.a);
	SDL_Rect page{ 0, 100, width, height - 100 };
	SDL_RenderFillRect(renderer, &page);

	_writeText(width / 2, height / 2, "PICK EM!!", black, font132);

}

void RenderWindow::_drawPredict() 
{
	SDL_SetRenderDrawColor(renderer, white.r, white.g, white.b, white.a);
	SDL_Rect page{ 0, 100, width, height - 100 };
	SDL_RenderFillRect(renderer, &page);

	_drawBack();

	SDL_Rect block;
	SDL_SetRenderDrawColor(renderer, purple.r, purple.g, purple.b, purple.a);
	block = { width / 2 - 90, height / 2 + 200, 180, 60 };
	SDL_RenderFillRect(renderer, &block);
	if (mPos.x >= width / 2 - 90 && mPos.x <= width / 2 + 90
		&& mPos.y <= height / 2 + 200 && mPos.y >= height / 2 + 260) {
		SDL_RenderFillRect(renderer, &block);
	}
	_writeText(width / 2, height / 2 + 230, "Clear", white, font34);

	_RenderFlags();

}

void RenderWindow::_drawResult() 
{
	SDL_SetRenderDrawColor(renderer, white.r, white.g, white.b, white.a);
	SDL_Rect page{ 0, 100, width, height - 100 };
	SDL_RenderFillRect(renderer, &page);

	_drawBack();

	SDL_Rect block;

	SDL_SetRenderDrawColor(renderer, purple.r, purple.g, purple.b, purple.a);
	block = {width/2 - 90, height/2 + 200, 180, 60};
	SDL_RenderFillRect(renderer, &block);
	if (mPos.x >= width / 2 - 90   && mPos.x <= width / 2 + 90 
	 && mPos.y <= height / 2 + 200 && mPos.y >= height / 2 + 260) {
		SDL_RenderFillRect(renderer, &block);
	}
	_writeText(width / 2, height / 2 + 230, "Compare", white, font34);
	if(count) {
		_writeText(width / 2, height / 2 + 190, "Please complete predicting", black, font12);
		count--;
	}

	_RenderFlags();

}

void RenderWindow::_drawHit()
{
	SDL_SetRenderDrawColor(renderer, white.r, white.g, white.b, white.a);
	SDL_Rect page{ 0, 100, width, height - 100 };
	SDL_RenderFillRect(renderer, &page);
	_writeText(width / 2, height / 2, "hit rate", black, font80);
	_writeText(width / 2, height / 2 + 80, hitRate, black, font80);

}

void RenderWindow::_RenderFlags() 
{
	if (stage == predict) {
		for (int i = 1; i < 32; i++) {
			if (pr[i].texture != empty) {
				_drawTexture(pr[i].texture, pr[i].x, pr[i].y);
			}
		}
	}
	else if (stage == result) {
		for (int i = 1; i < 32; i++) {
			if (rs[i].texture != empty) {
				_drawTexture(rs[i].texture, rs[i].x, rs[i].y);
			}
		}
	}
}

void RenderWindow::_drawTexture(SDL_Texture* texture, float x, float y) 
{
	SDL_Rect src;
	src.x = 0;
	src.y = 0;
	src.w;
	src.h;

	SDL_QueryTexture(texture, NULL, NULL, &src.w, &src.h);
	SDL_Rect dst;
	dst.x = x;
	dst.y = y;
	dst.w = src.w;
	dst.h = src.h;

	SDL_RenderCopy(renderer, texture, &src, &dst);
}

void RenderWindow::_drawBack() 
{
	for (int i = 1; i < 32; i++) {
		SDL_Rect rec;
		if (stage == predict) {
			if (pr[i].state == 1) {
				SDL_SetRenderDrawColor(renderer, green.r, green.g, green.b, green.a);
				pr[i].state = 0;
				rec = { pr[i].x - 3, pr[i].y - 3, block_width + 6, block_height + 6 };
				SDL_RenderFillRect(renderer, &rec);
			}
			else if (pr[i].state == 2) {
				SDL_SetRenderDrawColor(renderer, red.r, red.g, red.b, red.a);
				pr[i].state = 0;
				rec = { pr[i].x - 3, pr[i].y - 3, block_width + 6, block_height + 6 };
				SDL_RenderFillRect(renderer, &rec);
			}
		}
		if (stage == result) {
			if (rs[i].state == 1) {
				SDL_SetRenderDrawColor(renderer, green.r, green.g, green.b, green.a);
				rec = { rs[i].x - 3, rs[i].y - 3, block_width + 6, block_height + 6 };
				SDL_RenderFillRect(renderer, &rec);
			}
			else if (rs[i].state == 2) {
				SDL_SetRenderDrawColor(renderer, red.r, red.g, red.b, red.a);
				rec = { rs[i].x - 3, rs[i].y - 3, block_width + 6, block_height + 6 };
				SDL_RenderFillRect(renderer, &rec);
			}
		}

		SDL_SetRenderDrawColor(renderer, gray.r, gray.g, gray.b, gray.a);
		
		rec = { pr[i].x, pr[i].y, block_width, block_height };
		SDL_RenderFillRect(renderer, &rec);
	}

	// draw lines
	SDL_SetRenderDrawColor(renderer, black.r, black.g, black.b, black.a);
	for (int i = 31; i >= 4; i--) {
		if ((i >= 16 && i <= 23) || (i >= 8 && i <= 11) || i == 4 || i == 5)
			SDL_RenderDrawLine(renderer, pr[i].x + block_width, pr[i].y + (block_height / 2), pr[i / 2].x, pr[i / 2].y + (block_height / 2));
		if ((i >= 24 && i <= 31) || (i >= 12 && i <= 15) || i == 6 || i == 7)
			SDL_RenderDrawLine(renderer, pr[i].x, pr[i].y + (block_height / 2), pr[i / 2].x + block_width, pr[i / 2].y + (block_height / 2));
	}
	SDL_RenderDrawLine(renderer, pr[2].x + block_width, pr[2].y + (block_height / 2), pr[3].x, pr[3].y + (block_height / 2));
	SDL_RenderDrawLine(renderer, (pr[2].x + block_width + pr[3].x) / 2, pr[2].y + (block_height / 2), pr[1].x + (block_width / 2), pr[1].y + block_height);

}