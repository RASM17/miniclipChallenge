#include "../include/Game.h"

/**
	Buttons Enum for easier in Switch
*/

enum Button {
	START,
	QUIT,
	PUSHW,
	RESTART,
};

/**
	Game set all pointers to nullptr
	and clear vars
*/
Game::Game() {
	blockWall = nullptr;
	timer = nullptr;
	rend = nullptr;
	music = nullptr;
	isGameRunning = false;
	clearVars();
}


/**
	Inits SDL, the wall, the render manager and the timer (also starts the timer)
*/
void Game::init(const char* title, int xpos, int ypos) {
	if (SDL_Init(SDL_INIT_EVERYTHING) == 0) 	{
		std::cout << "Subsytems Initialised!" << std::endl;

		rend = new RenderManager(title, xpos, ypos);
		music = new MusicManager();
		blockWall = new BlockWall();

		timer = new Timer();
		isGameRunning = true;
	}
	else {
		isGameRunning = false;
	}
}

/**
	Clear all Vars to start a game
*/
void Game::clearVars() {
	blockMap.clear();
	for (int i = 0; i < BTYPES; i++) {
		blockMap[i] = 0;
	}
	isGamePaused = false;
	isGameOver = false;
	currentScore = 0;
	level = 1;
	maxLevelScore = MAXSCORE;
	if (timer != nullptr) {
		timer->stop();
	}
	if (blockWall != nullptr) {
		blockWall->clearBlockWall();
	}
}

/**
	Handle Events such as mouse or keyboard clicks
*/
void Game::handleEvent() {
	SDL_Event event;
	SDL_PollEvent(&event);

	switch (event.type)
	{
	case SDL_QUIT:
		isGameRunning = false;
		break;

	case SDL_KEYDOWN:
		if ((event.key.keysym.scancode == SDL_SCANCODE_ESCAPE || event.key.keysym.scancode == SDL_SCANCODE_P) && hasGameStarted) {
			isGamePaused = !isGamePaused;
			timer->pause();
			if (isGamePaused) {
				music->pause();
			}
			else {
				music->resume();
			}
		}
		break;

	case SDL_MOUSEBUTTONDOWN:
		if (hasGameStarted){
			if (isGameOver) {
				if (clickedButton(event.button.x, event.button.y, RESTART)) {
					start();
				}
			}
			else {
				if (blockWall != nullptr) {
					if (!isGamePaused) {
						// Get the row and column that was clicked
						int row = (event.button.y - WALL_Y1) / B_HEIGHT;
						int col = (event.button.x - WALL_X1) / B_WIDTH;
						std::cout << "Clicked on Row-> " << row << " Column-> "<< col << std::endl;
						// Check if click is inside the grid of blocks
						if (row >= 0 && row < NROWS && col >= 0 && col < NCOLS) {
							int bType = 0;
							bType = blockWall->getWall().matrix[row][col];
							std::cout << "Click in block type " << bType << std::endl;
							if (bType != 0) {
								deleteBlocks(row, col, bType);
							}
						}
						else {
							// Push Left Button
							if (clickedButton(event.button.x, event.button.y, PUSHW)) {
								timer->stop();
								blockWall->pushWallLeft();
								timer->start();
							}
						}
						
					}
				}
			}
		}
		else {
			isGameRunning = (!clickedButton(event.button.x, event.button.y, QUIT));

			if (clickedButton(event.button.x, event.button.y, START)) {
				start();
			}
		}
		break;
	default:
		break;
	}
}

/**
	Start a new game
*/
void Game::start() {
	clearVars();
	blockWall->initBlockWall();
	timer->start();
	hasGameStarted = true;
}

/**
	Update Game Logic
*/
void Game::update() {
	music->start();

	if (hasGameStarted || !isGamePaused || !isGameOver) {
		// Game over, block reached the End Zone
		// -1 because it goes from 0 to 4
		if (blockWall->getWall().matrix[NROWS - 1][0] != 0 && !isGameOver) {
			rend->setFinalScore(currentScore);
			isGameOver = true;
			std::cout << "Game over " << std::endl;
		}
		// Push the wall each interval and restarts timer
		if (timer->getGameTime() > (Uint32)PUSHT) {
			timer->stop();
			blockWall->pushWallLeft();
			timer->start();
		}
	}
}

/**
	Renders
*/
void Game::render() {
	SDL_RenderClear(rend->getRenderer());

	rend->renderBackground();

	if (!hasGameStarted)	{
		rend->renderMenu();
	}
	else {
		if (isGameOver) {
			music->stop();
			timer->stop();
			rend->renderGameOver(timer->getTimeElapsed(), blockMap);
		}
		else {
			if (isGamePaused) {
				rend->renderPause();
			}
			else {
				// Render HUD
				rend->renderHUD(timer->getGameTime(), currentScore, level);
				// Render Wall
				rend->renderGame(&blockWall->getWall());
			}
		}
	}

	SDL_RenderPresent(rend->getRenderer());
}

/**
	Clean vars and quit includes
*/
void Game::clean() {
	rend->~RenderManager();
	timer->~Timer();
	music->~MusicManager();

	Mix_Quit();
	TTF_Quit();
	IMG_Quit();
	SDL_Quit();
}

/**
	Check which button was clicked
	@param mouseX - X coords
	@param mouseY - Y coords
	@param btn - button
*/
bool Game::clickedButton(Sint32 mouseX, Sint32 mouseY, int btn)
{
	switch (btn)
	{
	case START:
		return mouseX >= START_BT_X && mouseX <= START_BT_X + BTN_WIDTH
			&& mouseY >= START_BT_Y && mouseY <= START_BT_Y + BTN_HEIGHT;
		break;

	case QUIT:
		return mouseX >= QUIT_BT_X && mouseX <= QUIT_BT_X + BTN_WIDTH
			&& mouseY >= QUIT_BT_Y && mouseY <= QUIT_BT_Y + BTN_HEIGHT;
		break;

	case PUSHW:
		return mouseX >= PUSHL_BTN_X && mouseX <= PUSHL_BTN_X + B_WIDTH
			&& mouseY >= PUSHL_BTN_Y && mouseY <= PUSHL_BTN_Y + B_HEIGHT;
		break;
	case RESTART:
		return mouseX >= RESTART_BTN_X && mouseX <= RESTART_BTN_X + B_WIDTH
			&& mouseY >= RESTART_BTN_Y && mouseY <= RESTART_BTN_Y + B_HEIGHT;
	default:
		return false;
		break;
	}
}


/**
	Delete block choosen and call sounds
	@param row - row
	@param col - column
	@param bType - Block Type
*/
void Game::deleteBlocks(int row, int col, int bType) {
	int nrBlocks = blockWall->breakBlock(row, col);
	std::cout << "Combo of : " << nrBlocks << std::endl;
	if (nrBlocks > 0) {
		currentScore += (nrBlocks * nrBlocks);
		checkLevel();

		// Check if bomb to apply different audio and not count to create a bomb
		switch (bType) {
			case 6:
				music->explosion();
				updateBlockCountWhenBomb();
				return;
			case 7:
			case 8:
				updateBlockCountWhenBomb();
				music->laser();
				return;
			default:
				music->click();
				break;
		}

		// Spawn Bomb if combo with more than BOMBSPAWN
		if (nrBlocks > BOMBSPAWN) {
			int rand = nrBlocks % NBOMBS;
			blockWall->setBlock(row, col, 6 + rand);
		}

		// -1 because 0 is empty and it doesnt matter for the stats
		updateBlockCount(bType - 1, nrBlocks);
	}
}

/**
	Keep track of which blocks were destroyed
	@param bType - Block Type
	@param nrBlocks - Number of blocks deleted
*/
void  Game::updateBlockCount(int bType, int nrBlocks) {
	if (blockMap.find(bType) != blockMap.end()) {
		blockMap[bType] += nrBlocks;
	}
	else {
		blockMap[bType] = nrBlocks;
	}
}

/**
	Keep track of which blocks were destroyed when a bomb is activated
*/
void  Game::updateBlockCountWhenBomb() {
	std::map<int, int> bombMap = this->blockWall->getMapBomb();
	std::map<int, int>::iterator it;
	// Iterate because we don't know which type of blocks were destroyed
	// Unlike blockmap that has all types for the score board
	for (it = bombMap.begin(); it != bombMap.end(); it++) {
		updateBlockCount(it->first, it->second);
	}
	// Clear map
	this->blockWall->clearMapBomb();
}

/**
	Check the score and if it levels Up
*/
void Game::checkLevel() {
	if (currentScore > maxLevelScore) {
		level++;
		std::cout << "New Level " << level << std::endl;
		maxLevelScore = MAXSCORE * level;
		music->levelUp();
	}
}