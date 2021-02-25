#pragma once


#include "SDL.h"
#include <SDL_mixer.h>
#include <iostream>
#include <string>

class MusicManager
{
public:
	MusicManager();
	~MusicManager();

	/**
	Start Music
	*/
	void start();
	/**
	Pause Music
	*/
	void pause();
	/**
	Resume Music
	*/
	void resume();
	/**
	Stop Music
	*/
	void stop();
	/**
	Play Click sound
	*/
	void click();
	/**
	Play Explosion sound
	*/
	void explosion();
	/**
	Play Level Up sound
	*/
	void levelUp();
	/**
	Play Laser sound
	*/
	void laser();

private:
	// Main Music
	Mix_Music* mainMusic = nullptr;
	// Sounds available to play
	Mix_Chunk* clickSound = nullptr;
	Mix_Chunk* explosionSound = nullptr;
	Mix_Chunk* levelUpSound = nullptr;
	Mix_Chunk* laserSound = nullptr;
};
