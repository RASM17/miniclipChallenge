#pragma once

#include "BlockWall.h"
#include "RenderManager.h"
#include "Timer.h"
#include "MusicManager.h"
#include <map>

class Game
{
public:
	/**
	Constructor
	Game set all pointers to nullptr
	and clear vars
	*/
	Game();
	/**
	Inits SDL, the wall, the render manager and the timer (also starts the timer)
	*/
	void init(const char* title, int xpos, int ypos);
	/**
	Clear all Vars to start a game
	*/
	void clearVars();
	/**
	Handle Events such as mouse or keyboard clicks
	*/
	void handleEvent();
	/**
	Update Game Logic
	*/
	void update();
	/**
	Renders
	*/
	void render();
	/**
	Clean vars and quit includes
	*/
	void clean();
	// Return running status
	bool running() { return isGameRunning; };

private:
	unsigned int currentScore, level, maxLevelScore;
	// Flags
	bool isGameRunning, hasGameStarted, isGamePaused, isGameOver;
	
	BlockWall* blockWall;
	Timer* timer;
	// Managers
	RenderManager* rend;
	MusicManager* music;

	// Map to have track of the blocks destroyed
	std::map<int, int> blockMap;
	/**
	Start a new game
	*/
	void start();
	/**
	Check which button was clicked
	@param mouseX - X coords
	@param mouseY - Y coords
	@param btn - button
	*/
	bool clickedButton(Sint32 mouseX, Sint32 mouseY, int btn);
	/**
	Delete block choosen and call sounds
	@param row - row
	@param col - column
	@param bType - Block Type
	*/
	void deleteBlocks(int row, int col, int bType);
	/**
	Check the score and if it levels Up
	*/
	void checkLevel();
	/**
	Keep track of which blocks were destroyed
	@param bType - Block Type
	@param nrBlocks - Number of blocks deleted
	*/
	void updateBlockCount(int bType, int nrBlocks);
	/**
	Keep track of which blocks were destroyed when a bomb is activated
	*/
	void updateBlockCountWhenBomb();
};