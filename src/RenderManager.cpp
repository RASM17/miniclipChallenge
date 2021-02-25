#include "../include/RenderManager.h"

/**
	Init render and vars
*/
RenderManager::RenderManager(const char* _title, int _xpos, int _ypos)
{
	finalScore = 0;
	timerRect = {};
	renderer = nullptr;
	text_font = nullptr;
	subText_font = nullptr;
	Title_font = nullptr;

	// Create window with information present on main.cpp
	window = SDL_CreateWindow(_title, _xpos, _ypos, SCREEN_WIDTH, SCREEN_HEIGHT, FULLSCREEN ? SDL_WINDOW_FULLSCREEN : 0);
	if (window == NULL) {
		std::cout << "Error creating window: " << SDL_GetError() << std::endl;
		return;
	}

	// Create vsynced renderer for the created window
	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
	if (renderer == NULL)
	{
		std::cout << "Error creating renderer: " << SDL_GetError() << std::endl;
		return;
	}
	else
	{
		//Set texture filtering to linear
		if (!SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "1"))
		{
			printf("Linear texture filtering not enabled!");
		}
	}

	// Init PNG loading
	int _imgFlags = IMG_INIT_PNG;
	if (!(IMG_Init(_imgFlags) & _imgFlags))
	{
		std::cout << "SDL Image init error :" << IMG_GetError() << std::endl;
		return;
	}

	//Init SDL_TTF
	if (TTF_Init() == -1)
	{
		std::cout << "SDL_TTF init error :" << TTF_GetError() << std::endl;
		return;
	}
	initTextures();
}

/**
	Render desconctruct
	clears vars and free textures,render and window
*/
RenderManager::~RenderManager()
{
	// Free block, bombs, text and button textures 
	for (auto elemt : block_tex) {
		elemt.free();
	}
	for (auto elemt : bomb_tex) {
		elemt.free();
	}

	background_tex.free();
	timer_tex.free();
	score_tex.free();
	pushWall_btn.free();
	endZone_tex.free();

	gameOver_tex.free();
	timeElapsed_tex.free();
	finalScore_tex.free();
	pause_tex.free();
	start_btn.free();
	restart_btn.free();
	scoreboard.free();
	quit_btn.free();

	for (auto elemt: blockScore_tex) {
		elemt.free();;
	}

	// Free font
	TTF_CloseFont(text_font);
	text_font = nullptr;
	TTF_CloseFont(subText_font);
	subText_font = nullptr;
	TTF_CloseFont(Title_font);
	Title_font = nullptr;

	// Destroy renderer
	SDL_DestroyRenderer(renderer);
	renderer = nullptr;
	// Destory window
	SDL_DestroyWindow(window);
	window = nullptr;
}

/**
	Inits textures and the matrix of blocks
*/
void RenderManager::initTextures()
{
	//Background
	background_tex = TextureManager(renderer);
	background_tex.loadImage("assets/background.png");

	//Blocks
	for (int i = 0; i < BTYPES; i++) {
		block_tex[i].setRend(renderer);
		block_tex[i].loadImage("assets/block_" + std::to_string((i)) + ".png");
	}

	for (int i = 0; i < NBOMBS; i++) {
		bomb_tex[i].setRend(renderer);
		bomb_tex[i].loadImage("assets/miniclip_bomb_" + std::to_string((i)) + ".png");
	}

	//Buttons
	start_btn = TextureManager(renderer);
	start_btn.loadImage("assets/start_btn.png");

	quit_btn = TextureManager(renderer);
	quit_btn.loadImage("assets/quit_btn.png");

	pushWall_btn = TextureManager(renderer);
	pushWall_btn.loadImage("assets/pushWall_btn.png");

	restart_btn = TextureManager(renderer);
	restart_btn.loadImage("assets/restart_btn.png");

	scoreboard = TextureManager(renderer);
	scoreboard.loadImage("assets/scoreboard.png");

	//Open the Font
	text_font = TTF_OpenFont("assets/Minecraft.ttf", TEXT_SIZE);
	subText_font = TTF_OpenFont("assets/Minecraft.ttf", SUBTEXT_SIZE);
	Title_font = TTF_OpenFont("assets/Minecraft.ttf", TITLE_SIZE);

	if (text_font == NULL || subText_font == NULL || Title_font == NULL) {
		std::cout << "Error loading font: " << TTF_GetError() << std::endl;
	}
	else {
		//Render text
		for (int i = 0; i < 5; i++) {
			blockScore_tex[i] = TextureManager(renderer);
		}
		gameOver_tex = TextureManager(renderer);
		timeElapsed_tex = TextureManager(renderer);
		finalScore_tex = TextureManager(renderer);
		pause_tex = TextureManager(renderer);
		timer_tex = TextureManager(renderer);
		score_tex = TextureManager(renderer);
		endZone_tex = TextureManager(renderer);
	}
}

/**
	Render Background Image
*/
void RenderManager::renderBackground() {
	background_tex.setCoords(0, 0);
	background_tex.render();
}

/**
	Render main menu
	With start and quit buttons
*/
void RenderManager::renderMenu() {
	start_btn.setCoords(START_BT_X, START_BT_Y);
	start_btn.render();

	quit_btn.setCoords(QUIT_BT_X, QUIT_BT_Y);
	quit_btn.render();
}


/**
	Render Game Over Screen
	@param elapsedTime - Time Elapsed playing until now
*/
void RenderManager::renderGameOver(Uint32 elapsedTime, std::map<int, int> blockMap) {
	renderGameOverText();
	renderFinalSRC();
	renderTimeElapsed(elapsedTime);
	scoreboard.setCoords(SCRBOARD_X, SCRBOARD_Y);
	scoreboard.render();
	for (auto elem : blockMap)	{
		renderBlockCount(elem.first, elem.second);
	}
	restart_btn.setCoords(RESTART_BTN_X, RESTART_BTN_Y);
	restart_btn.render();
}

/**
	Render Block Count
	@param bType - Block Type
	@param nrBlocks - Number of blocks
*/
void RenderManager::renderBlockCount(int bType, int nrBlocks) {
	if (!blockScore_tex[bType].loadText(std::to_string(nrBlocks), BLACK, subText_font)) {
		std::cout << "Failed rendering nrBlocks text of type"<< bType << std::endl;
	}
	blockScore_tex[bType].setCoords(SCRBLOCK_TXT_X, SCRBLOCK_TXT_Y + SCRBLOCK_TXT_INTERVAL * bType);
	blockScore_tex[bType].render();
}

/**
	Render Time Elapse text
	@param elapsedTime - Time Elapsed playing until now
*/
void RenderManager::renderTimeElapsed(Uint32 elapsedTime) {
	std::stringstream timeStream;
	// Convert ms to s and fixed 3 decimals
	timeStream << std::fixed << std::setprecision(3) << ((float)elapsedTime/1000);
	if (!timeElapsed_tex.loadText("Time: " + timeStream.str() + " seconds", BLACK, text_font)) {
		std::cout << "Failed rendering time elapsed text" << std::endl;
	}
	timeElapsed_tex.setCoords(TELAP_TXT_X, TELAP_TXT_Y);
	timeElapsed_tex.render();
}

/**
	Render Final score
*/
void RenderManager::renderFinalSRC() {
	if (!finalScore_tex.loadText(std::to_string(finalScore), BLACK, text_font)) {
		std::cout << "Failed rendering final score text" << std::endl;
	}
	finalScore_tex.setCoords(FSCR_TXT_X, FSCR_TXT_Y);
	finalScore_tex.render();
}

/**
	Render Game Over text
*/
void RenderManager::renderGameOverText() {
	if (!gameOver_tex.loadText("Game Over", BLACK, Title_font)) {
		std::cout << "Failed rendering Game Over text" << std::endl;
	}
	gameOver_tex.setCoords(GAMEOVER_TXT_X - (gameOver_tex.getWidth()/4), GAMEOVER_TXT_Y - (gameOver_tex.getHeight() / 4));
	gameOver_tex.render();
}

/**
	Render Pause Text
*/
void RenderManager::renderPause() {
	if (!pause_tex.loadText("Pause", BLACK, subText_font)) {
		std::cout << "Failed rendering pause text" << std::endl;
	}
	pause_tex.setCoords(PAUSED_TXT_X, PAUSED_TXT_Y);
	pause_tex.render();
}

/**
	Render End Zone, Block Wall, Push Wall Left button
	@param blockWall - Wall composed of blocks
*/
void RenderManager::renderGame(blockWallStruct* blockWall) {
	renderEndZone();
	renderBlockWall(blockWall);
	pushWall_btn.setCoords(PUSHL_BTN_X, PUSHL_BTN_Y);
	pushWall_btn.render();
}

/**
	Render HUD containing Time Bar and current score
	@param currTime - current Time
	@param currScore - current Score
	@param level - current Level
*/
void RenderManager::renderHUD(Uint32 currTime, int currScore, int level) {
	renderBar(currTime);
	renderPush(currTime);
	renderLvl(level);
	renderScore(currScore);	
}

/**
		Render Current level
		@param level
*/
void RenderManager::renderLvl(int level) {
	if (!timer_tex.loadText("Level: " + std::to_string(level), BLACK, text_font)) {
		std::cout << "Failed rendering Level" << std::endl;
	}
	timer_tex.setCoords(LVL_TXT_X, LVL_TXT_Y);
	timer_tex.render();
}

/**
	Render Time Bar
	@param currTime - current Time
*/
void RenderManager::renderBar(Uint32 currTime) {
	// Get bar width with 3 simple Rule
	int barWidth = TM_MAX_WIDTH - (((float)currTime / PUSHT) * TM_MAX_WIDTH);
	timerRect = { (int) (TM_TXT_X + timer_tex.getWidth()), TM_TXT_Y, barWidth, (int) timer_tex.getHeight() };
	SDL_SetRenderDrawColor(renderer, 181, 7, 7, 255);
	SDL_RenderFillRect(renderer, &timerRect);
}

/**
	Render Push Text
	@param currTime - current Time
*/
void RenderManager::renderPush(Uint32 currTime) {
	if (!timer_tex.loadText("Push: ", BLACK, text_font)) {
		std::cout << "Failed rendering timer" << std::endl;
	}
	timer_tex.setCoords(TM_TXT_X, TM_TXT_Y);
	timer_tex.render();
}

/**
	Render Score Text
	@param currScore - Current Score of player
*/
void RenderManager::renderScore(int currScore) {
	if (!score_tex.loadText("Score: " + std::to_string(currScore), BLACK, text_font))
	{
		std::cout << "Failed rendering score" << std::endl;
	}
	score_tex.setCoords(SCR_TXT_X, SCR_TXT_Y);
	score_tex.render();
}

/**
	Render Block Wall 
	@param blockWall -  Wall composed of blocks
*/
void RenderManager::renderBlockWall(blockWallStruct* blockWall) {
	for (int i = 0; i < NROWS; i++) {
		for (int j = 0; j < NCOLS; j++) {
			int bType = blockWall->matrix[i][j];
			// If 0 no need to render block
			if (bType != 0) {
				renderBlock(bType, i, j);
			}
		}
	}
}

/**
	Render Block
*/
void RenderManager::renderBlock(int bType, int row, int col) {
	// Render Blocks
	if (bType <= BTYPES) {
		// 0 means empty in BTYPES
		// -1 Since array goes from 0 to 4
		block_tex[bType - 1].setCoords((col * B_WIDTH) + WALL_X1, (row * B_HEIGHT) + WALL_Y1);
		block_tex[bType - 1].render();
	}
	else {
		// 0 means empty in BTYPES
		// -1 Since array goes from 0 to 4 and - BTYPES because the others represent normal blocks
		bomb_tex[bType - 1 - BTYPES].setCoords((col * B_WIDTH) + WALL_X1, (row * B_HEIGHT) + WALL_Y1);
		bomb_tex[bType - 1 - BTYPES].render();
	}
}

/**
	Render End Zone Line and Text
*/
void RenderManager::renderEndZone() {
	if (!endZone_tex.loadText("End Zone", BLACK, text_font)) {
		std::cout << "Failed rendering end zone" << std::endl;
	}
	endZone_tex.setCoords(WALL_X1 - (endZone_tex.getWidth()/2), WALL_Y1 - (endZone_tex.getHeight()));
	endZone_tex.render();

	// Grey Line
	SDL_SetRenderDrawColor(renderer, 128, 128, 128, 128);
	SDL_RenderDrawLine(renderer, WALL_X1, WALL_Y1,  WALL_X1, WALL_Y2);
}