#pragma once
#include "SDL_image.h"
//********** Game Settings**********

//***** Display Settings*****
// Screen size
constexpr bool FULLSCREEN = false;
constexpr unsigned int SCREEN_WIDTH = 700;
constexpr unsigned int SCREEN_HEIGHT = 500;
// Fonts Sizes
constexpr unsigned int TEXT_SIZE = 32;
constexpr unsigned int SUBTEXT_SIZE = 40;
constexpr unsigned int TITLE_SIZE = 64;
// Buttons Sizes
constexpr unsigned int BTN_WIDTH = 175;
constexpr unsigned int BTN_HEIGHT = 50;
// Block Width and Height (depends on image size)
constexpr unsigned int B_WIDTH = 32;
constexpr unsigned int B_HEIGHT = 32;
// SDL color used in text
constexpr SDL_Color BLACK = { 0, 0, 0, 0 };

//***** Game*****
// FPS
const unsigned int FPS = 60;
const unsigned int frameDelay = 1000 / FPS;

// Number of Block types
constexpr unsigned int BTYPES = 5;
// Number of Bombs Types
constexpr unsigned int NBOMBS = 3;
// Time to wall move to be pushed
constexpr float PUSHT = 5000;
// Score for 1st level after is lvl* 100
constexpr unsigned int MAXSCORE = 100;
// Bomb effects
constexpr unsigned int BOMBEFFECT = 1;
// Bomb spawn condition, if a combo superior to this number, then a bomb will spawn
constexpr unsigned int BOMBSPAWN = 3;

//***** Wall Settings*****
// Number of rows and columns for the Block Wall
constexpr unsigned int NROWS = 8;
constexpr unsigned int NCOLS = 15;
// Block Wall width and height
constexpr unsigned int W_WIDTH = (B_WIDTH * NCOLS);
constexpr unsigned int W_HEIGHT = (B_HEIGHT * NROWS);
// Starting column when creating a new Block Wall
constexpr unsigned int STARTCOL = (NCOLS / 2);
// Block Wall Coords
constexpr unsigned int WALL_X1 = (SCREEN_WIDTH - W_WIDTH); //So it fits the screen
constexpr unsigned int WALL_X2 = SCREEN_WIDTH;
constexpr unsigned int WALL_Y1 = ((SCREEN_HEIGHT - W_HEIGHT) / 2)- 20; // Where the land is in the image
constexpr unsigned int WALL_Y2 = (W_HEIGHT + WALL_Y1);

//***** Main Menu SCREEN*****
// Start Button
constexpr unsigned int START_BT_X = (SCREEN_WIDTH / 2) - (BTN_WIDTH/2); // Right in the midle with the button centered
constexpr unsigned int START_BT_Y = (SCREEN_HEIGHT / 4) - (BTN_HEIGHT);
// Quit Button
constexpr unsigned int QUIT_BT_X = START_BT_X;
constexpr unsigned int QUIT_BT_Y = (SCREEN_HEIGHT / 4) + (BTN_HEIGHT);

//***** Pause SCREEN*****
// Pause text
constexpr unsigned int PAUSED_TXT_X = 0;
constexpr unsigned int PAUSED_TXT_Y = 0;

//***** GAME OVER SCREEN*****
// Game over text
constexpr unsigned int GAMEOVER_TXT_X = (SCREEN_WIDTH / 2);
constexpr unsigned int GAMEOVER_TXT_Y = (SCREEN_HEIGHT / 2) - 50;
// Final Score
constexpr unsigned int FSCR_TXT_X = 160;
constexpr unsigned int FSCR_TXT_Y = 40;
// Time Elapsed
constexpr unsigned int TELAP_TXT_X = 300;
constexpr unsigned int TELAP_TXT_Y = 64;
// Retart button
constexpr unsigned int RESTART_BTN_X = (SCREEN_WIDTH - 2*B_WIDTH);
constexpr unsigned int RESTART_BTN_Y = B_HEIGHT;
// Scoreboard
constexpr unsigned int SCRBOARD_X = B_WIDTH;
constexpr unsigned int SCRBOARD_Y = B_HEIGHT;
// Block score
constexpr unsigned int SCRBLOCK_TXT_X = 150;
constexpr unsigned int SCRBLOCK_TXT_Y = 95;
// Space between block scores
constexpr unsigned int SCRBLOCK_TXT_INTERVAL = 45;

//***** HUD *****
// Score text
constexpr unsigned int SCR_TXT_X = 0;
constexpr unsigned int SCR_TXT_Y = 0;
// Level Text
constexpr unsigned int LVL_TXT_X = (SCREEN_WIDTH/4);
constexpr unsigned int LVL_TXT_Y = 0;
// Timer Text and Bar
constexpr unsigned int TM_TXT_X = 3 *(SCREEN_WIDTH / 5);
constexpr unsigned int TM_TXT_Y = 0;
constexpr float TM_MAX_WIDTH = 100;
// Next stage button
constexpr unsigned int PUSHL_BTN_X = (WALL_X2 - 2*B_WIDTH);
constexpr unsigned int PUSHL_BTN_Y = (WALL_Y2 + B_HEIGHT);