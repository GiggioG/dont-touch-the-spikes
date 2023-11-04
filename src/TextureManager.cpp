#include "TextureManager.h"
#include "Presenter.h"


SDL_Texture* TextureManager::menu_background_texture = nullptr;
SDL_Texture* TextureManager::game_background_texture = nullptr;

SDL_Texture* TextureManager::play_button_texture = nullptr;
SDL_Texture* TextureManager::quit_button_texture = nullptr;

SDL_Texture* TextureManager::pile1_texture = nullptr;
SDL_Texture* TextureManager::pile2_texture = nullptr;
SDL_Texture* TextureManager::spike_texture = nullptr;
SDL_Texture* TextureManager::longSpikes_texture = nullptr;
SDL_Texture* TextureManager::bonbon_texture = nullptr;
SDL_Texture* TextureManager::gameOverlay_texture = nullptr;
SDL_Texture* TextureManager::multiplierX_texture = nullptr;

SDL_Texture* TextureManager::playAgain_button_texture = nullptr;
SDL_Texture* TextureManager::scoresbackground_texture = nullptr;

TextureManager::TextureManager() {}
TextureManager::~TextureManager() {}

void TextureManager::init() {
	menu_background_texture = loadTexture(cfgm->cfg["MENU_BACKGROUND_BMP"].s);
	game_background_texture = loadTexture(cfgm->cfg["GAME_BACKGROUND_BMP"].s);

	play_button_texture = loadTexture(cfgm->cfg["PLAY_BUTTON_BMP"].s);
	quit_button_texture = loadTexture(cfgm->cfg["QUIT_BUTTON_BMP"].s);

	pile1_texture = loadTexture(cfgm->cfg["PILE1_BMP"].s);
	pile2_texture = loadTexture(cfgm->cfg["PILE2_BMP"].s);
	spike_texture = loadTexture(cfgm->cfg["SPIKE_BMP"].s);
	longSpikes_texture = loadTexture(cfgm->cfg["LONGSPIKES_BMP"].s);
	bonbon_texture = loadTexture(cfgm->cfg["BONBON_BMP"].s);
	gameOverlay_texture = loadTexture(cfgm->cfg["GAME_OVERLAY_BMP"].s);
	multiplierX_texture = loadTexture(cfgm->cfg["MULTIPLIER_X_BMP"].s);

	playAgain_button_texture = loadTexture(cfgm->cfg["PLAYAGAIN_BUTTON_TEXTURE"].s);
	scoresbackground_texture = loadTexture(cfgm->cfg["SCORES_BKG_TEXTURE"].s);
}

void TextureManager::destruct() {
	SDL_DestroyTexture(menu_background_texture);
	SDL_DestroyTexture(game_background_texture);

	SDL_DestroyTexture(play_button_texture);
	SDL_DestroyTexture(quit_button_texture);

	SDL_DestroyTexture(pile1_texture);
	SDL_DestroyTexture(pile2_texture);
	SDL_DestroyTexture(spike_texture);
	SDL_DestroyTexture(longSpikes_texture);
	SDL_DestroyTexture(gameOverlay_texture);
	SDL_DestroyTexture(multiplierX_texture);

	SDL_DestroyTexture(playAgain_button_texture);
	SDL_DestroyTexture(scoresbackground_texture);
}