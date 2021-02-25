#pragma once

#include "SDL.h"
#include "SDL_image.h"
#include "SDL_ttf.h"
#include <iostream>
#include <string>

/************************
* Class Texture:
*				Responsible to create Textures
************************/

class TextureManager
{
public:
	// Inits texture
	TextureManager();
	TextureManager(SDL_Renderer* rend);

	// Destroys texture
	void free();
	~TextureManager() { free(); };

	/**
	Renders texture at the current location, with current size
	*/
	void render();
	// Get sizes of texture
	unsigned int getHeight() { return tex_h; };
	unsigned int getWidth() { return tex_w; };
	// Get coords of texture
	unsigned int Xcoord() { return tex_x; };
	unsigned int Ycoord() { return tex_y; };
	// Set Coords of texture
	void setCoords(unsigned int x, unsigned int y) {
		tex_x = x;
		tex_y = y;
	}

	/**
		Sets renderer
		@param ren - renderer
	*/
	void setRend(SDL_Renderer* ren) { rend = ren; };

	/**
		Loads texture from image given path
		@param path - path for image
	*/
	bool loadImage(std::string path);

	/**
		Load texture from inputed text
		@param text - text to be rendered
		@param color - color of texture
		@param font - font to be used
	*/
	bool loadText(std::string text, SDL_Color color, TTF_Font* font);

private:
	// Texture
	SDL_Texture* tex;
	// Renderer
	SDL_Renderer* rend;
	/**
	Reset Variables to default values
	*/
	void reset();
	// Coords and Sizes of textures
	unsigned int  tex_x, tex_y, tex_w, tex_h;
};