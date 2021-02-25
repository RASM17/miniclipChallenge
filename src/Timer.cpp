#include "../include/Timer.h"

/**
	Constructor
*/
Timer::Timer() {
	reset();
}

/**
	Descontructor
*/
Timer::~Timer(){
}

/**
	Start Timer
*/
void Timer::start() {
	started = true;
	paused = false;

	// Get current time
	start_ticks = SDL_GetTicks();
	paused_ticks = 0;
}

/**
	Stop Timer
*/
void Timer::stop() {
	if (started) {
		elapedTime = start_ticks;
		reset();
	}
}

/**
	Clear Timer Variables
*/
void Timer::reset() {
	started = false;	
	paused = false;
	start_ticks = 0;
	paused_ticks = 0;
}

/**
	Resume / Pause Game
*/
void Timer::pause() {
	if (started) {
		if (paused) {
			paused = false;
			// Subtrack elapsed time to get a total of time spent playing
			start_ticks = SDL_GetTicks() - paused_ticks;
			paused_ticks = 0;
		}
		else {
			paused = true;
			// Elapsed time
			paused_ticks = SDL_GetTicks() - start_ticks;
			start_ticks = 0;
		}
	}
}

/**
	Get Elapsed time playing
*/
Uint32 Timer::getGameTime() {
	Uint32 nTicks = 0;
	if (started){
		if (paused) {
			nTicks = paused_ticks;
		}
		else {
			nTicks = SDL_GetTicks() - start_ticks;
		}
	}
	return nTicks;
}
