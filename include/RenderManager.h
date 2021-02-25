#pragma once

#include "TextureManager.h"
#include "BlockWall.h"
#include <iomanip>
#include <sstream>
#include <map>
/************************
* Class Texture:
*				Responsible to render text and objects
************************/

class RenderManager
{
public:
	RenderManager(const char* title, int xpos, int ypos);
	~RenderManager();

	// Renderer
	SDL_Renderer* getRenderer() { return renderer; };
	// Window
	SDL_Window* getWindow() { return window; };
	/**
	Render Background Image
	*/
	void renderBackground();	
	/**
	Render main menu
	With start and quit buttons
	*/
	void renderMenu();	
	/**
	Render Pause Text
	*/
	void renderPause();
	/**
	Render Game Over Screen
	@param elapsedTime - Time Elapsed playing until now
	*/
	void renderGameOver(Uint32 timeElapsed, std::map<int, int> blockMap);
	// You lost screen
	/**
	Render End Zone, Block Wall, Push Wall Left button
	@param blockWall - Wall composed of blocks
	*/
	void renderGame(blockWallStruct* blockWall);
	/**
	Render HUD containing Time Bar and current score
	@param currTime - current Time
	@param currScore - current Score
	@param level - current Level
	*/
	void renderHUD(Uint32 currTime, int currScore, int level);	
	/**
	Save score to display
	@param score - Score of the player
	*/
	void setFinalScore(int score) { finalScore = score; };
	/**
	Inits textures and the matrix of blocks
	*/
	void initTextures();
	/**
	Render Block Wall
	*/
	void renderBlockWall(blockWallStruct* blockWall);
	/**
	Render Block
	*/
	void renderBlock(int bType, int row, int col);
	/**
	Render End Zone Line
	*/
	void renderEndZone();
	/**
	Render Score Text
	@param currScore - Current Score of player
	*/
	void renderScore(int currScore);
	/**
	Render Push Text
	@param currTime - current Time
	*/
	void renderPush(Uint32 currTime);
	/**
	Render Time Bar
	@param currTime - current Time
	*/
	void renderBar(Uint32 currTime);
	/**
	Render Game Over text
	*/
	void renderGameOverText();
	/**
	Render Final score text
	*/
	void renderFinalSRC();
	/**
	Render Time Elapse text
	@param elapsedTime - Elapsed time
	*/
	void renderTimeElapsed(Uint32 elapsedTime);
	/**
		Render Current level
		@param level
	*/
	void renderLvl(int level);
	/**
		Render Block Count
		@param bType - Block Type
		@param nrBlocks - Number of blocks
	*/
	void renderBlockCount(int bType, int nrBlocks);

private:
	SDL_Window* window;
	SDL_Renderer* renderer;

	// Textures from text
	TextureManager
		timer_tex,							// Timer text
		pause_tex,							// Paused text
		gameOver_tex,						// Game Over text
		endZone_tex,						// End zone text
		score_tex,							// Score text
		finalScore_tex,						// Final score text
		blockScore_tex[BTYPES],				// Array with block scores
		timeElapsed_tex;					// Time Elapsed
	//Textures from images
	TextureManager
		background_tex,						// Background image
		pushWall_btn,						// Push wall button
		start_btn,							// Menu start button
		restart_btn,						// Restart button
		quit_btn,							// Menu quit button
		block_tex[BTYPES],					// Array of Blocks textures
		scoreboard,							// Scoreboard
		bomb_tex[NBOMBS];					// Array of bomb textures

	// Fonts sizes
	TTF_Font* text_font, * subText_font, * Title_font;
	// Timer rectangle 
	SDL_Rect timerRect;
	// Final score
	unsigned int finalScore;
};