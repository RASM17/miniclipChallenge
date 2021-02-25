#include "../include/MusicManager.h"

/**
	Initialize Music Manager
*/
MusicManager::MusicManager()
{
	// Initialize SDL_mixer
	if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 1024) < 0) 	{
		std::cout << "Mixer could not initialize!" << Mix_GetError() << std::endl;
	}
	else {
		// Load music
		mainMusic = Mix_LoadMUS("assets/tetris_theme_piano.mp3");
		if (!mainMusic) {
			std::cout << "Failed to load menu music" << Mix_GetError() << std::endl;
		}
		// Load click sound
		clickSound = Mix_LoadWAV("assets/mario_jump.wav");
		if (!clickSound) {
			std::cout << "Failed to load click sound" << Mix_GetError() << std::endl;
		}
		// Load explosion sound
		explosionSound = Mix_LoadWAV("assets/space_invaders_explosion.wav");
		if (!explosionSound) {
			std::cout << "Failed to load explosion sound" << Mix_GetError() << std::endl;
		}
		// Load level up sound
		levelUpSound = Mix_LoadWAV("assets/final_fantasy_level_up.wav");
		if (!levelUpSound) {
			std::cout << "Failed to load level up sound" << Mix_GetError() << std::endl;
		}
		// Load laser sound
		laserSound = Mix_LoadWAV("assets/laser.wav");
		if (!levelUpSound) {
			std::cout << "Failed to load laser sound" << Mix_GetError() << std::endl;
		}

	}
}

/**
	Destruct Music
*/
MusicManager::~MusicManager() {
	Mix_FreeMusic(mainMusic);
	mainMusic = nullptr;
	Mix_FreeChunk(clickSound);
	clickSound = nullptr;
	Mix_FreeChunk(explosionSound);
	explosionSound = nullptr;
}

/**
	Start Music
*/
void MusicManager::start() {
	if (Mix_PlayingMusic() == 0) {
		Mix_PlayMusic(mainMusic, -1);
	}
}

/**
	Pause Music
*/
void MusicManager::pause() {
	if (Mix_PlayingMusic())	{
		Mix_PauseMusic();
	}
}

/**
	Resume Music
*/
void MusicManager::resume() {
	if (Mix_PausedMusic() == 1){
		Mix_ResumeMusic();
	}
}

/**
	Stop Music
*/
void MusicManager::stop() {
	if (Mix_PlayingMusic()) {
		Mix_HaltMusic();
	}
}

/**
	Play Click sound
*/
void MusicManager::click() {
	Mix_PlayChannel(-1, clickSound, 0);
}

/**
	Play Explosion sound
*/
void MusicManager::explosion() {
	Mix_PlayChannel(-1, explosionSound, 0);
}

/**
	Play Level Up sound
*/
void MusicManager::levelUp() {
	Mix_PlayChannel(-1, levelUpSound, 0);
}

/**
	Play Laser sound
*/
void MusicManager::laser() {
	Mix_PlayChannel(-1, laserSound, 0);
}
