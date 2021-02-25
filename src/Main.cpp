#include "../include/Game.h"
Game* game = nullptr;

int main(int argc, char* argv[]) {
	Uint32 frameStart;
	unsigned int frameTime;

	game = new Game();
	game->init("Miniclip Task", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED);

	// Game is running
	while (game->running())	{

		frameStart = SDL_GetTicks();

		game->handleEvent();			// Handles window and mouse events
		game->update();					// Updates game
		game->render();					// Display new Updates

		// Main 60 FPS indepent of the screen refresh Rate
		// This way all users will experience the same game
		frameTime = SDL_GetTicks() - frameStart;
		if (frameDelay > frameTime) {
			SDL_Delay(frameDelay - frameTime);
		}
	}

	game->clean();						//Clean Renderer and close game
	return 0;
}