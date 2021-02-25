#include "../include/TextureManager.h"


TextureManager::TextureManager() {
	reset();
	rend = nullptr;
}

/**
	Constructor with renderer
*/
TextureManager::TextureManager(SDL_Renderer* ren) {
	reset();
	rend = ren;
}

/**
	Reset Variables to default values
*/
void TextureManager::reset() {
	tex = nullptr;
	tex_w = 0;
	tex_h = 0;
	tex_x = 0;
	tex_y = 0;
}

/**
	Destroys texture
*/
void TextureManager::free(){
	if (tex != NULL) {
		SDL_DestroyTexture(tex);
		reset();
	}
}

void TextureManager::render() {
	SDL_Rect destRect = { tex_x, tex_y, tex_w, tex_h };
	SDL_RenderCopy(rend, tex, NULL, &destRect);
}

/**
	Loads texture from image given path
	@param path - path for image
*/
bool TextureManager::loadImage(std::string path) {
	// Clear Texture if exists
	free();

	// Load image from given path
	SDL_Surface* tempSurface = IMG_Load(path.c_str());
	if (tempSurface == NULL) {
		std::cout << "Image Load Error" << IMG_GetError << std::endl;
		return false;
	}
	else {
		// Use Temp Surface to create Texture
		tex = SDL_CreateTextureFromSurface(rend, tempSurface);

		if (tex == NULL) {
			std::cout << "Texture Creation Error" << SDL_GetError << std::endl;
			return false;
		}
		else {
			// Save Texture Dimensions
			tex_w = tempSurface->w;
			tex_h = tempSurface->h;
		}
		// free Temp Surface
		SDL_FreeSurface(tempSurface);
	}

	return true;
}

/**
	Load texture from inputed text
	@param text - text to be rendered
	@param color - color of texture
	@param font - font to be used
*/
bool TextureManager::loadText(std::string text, SDL_Color color, TTF_Font* font)
{
	// Clear Texture
	free();

	//Render text to surface
	SDL_Surface* tempSurface = TTF_RenderText_Solid(font, text.c_str(), color);
	if (tempSurface == NULL) {
		std::cout << "Text Load Error" << TTF_GetError << std::endl;
		return false;
	}
	else {
		// Use Temp Surface to create Texture
		tex = SDL_CreateTextureFromSurface(rend, tempSurface);
		if (tex == NULL) {
			std::cout << "Text Texture Creation Error" << SDL_GetError << std::endl;
			return false;
		}
		else {
			// Save Texture Dimensions
			tex_w = tempSurface->w;
			tex_h = tempSurface->h;
		}
		SDL_FreeSurface(tempSurface);
	}
	return true;
}
