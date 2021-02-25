#pragma once

#include <SDL.h>
#include <stdio.h>
#include <string>
#include <sstream>

/************************
* Class Timer:
*				Responsibel to control the timer of the game
************************/
class Timer
{
public:
	Timer();
	~Timer();

	/**
	Start Timer
	*/
	void start();
	/**
		Stop timer
	*/
	void stop();
	/**
		Resume / Pause Game
	*/
	void pause();
	/**
		Clear Timer Variables
	*/
	void reset();
	/**
		Get Elapsed time playing
		@return nTicks - Elapsed Time
	*/
	Uint32 getGameTime();
	Uint32 getTimeElapsed() { return elapedTime; };

private:
	// Vars used to calculate played time
	Uint32 start_ticks, paused_ticks, elapedTime;

	//Timer status
	bool paused, started;
};