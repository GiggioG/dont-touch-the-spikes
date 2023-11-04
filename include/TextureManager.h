#pragma once

#include "defines.h"
#include "ConfigManager.h"

extern ConfigManager* cfgm;

class TextureManager {
public:
	TextureManager();
	~TextureManager();

	static SDL_Texture* menu_background_texture;
	static SDL_Texture* game_background_texture;

	static SDL_Texture* play_button_texture;
	static SDL_Texture* quit_button_texture;

	static SDL_Texture* pile1_texture;
	static SDL_Texture* pile2_texture;
	static SDL_Texture* spike_texture;
	static SDL_Texture* longSpikes_texture;
	static SDL_Texture* bonbon_texture;
	static SDL_Texture* gameOverlay_texture;
	static SDL_Texture* multiplierX_texture;

	static SDL_Texture* playAgain_button_texture;
	static SDL_Texture* scoresbackground_texture;

	void init();
	void destruct();
};