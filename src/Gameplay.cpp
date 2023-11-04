#include "defines.h"
#include "World.h"
#include "Gameplay.h"
#include "TextureManager.h"
#include "Presenter.h"

#define CURR_PLAYER "[P" << turn << "]"

extern World world;

Gameplay::Gameplay() {}
Gameplay::~Gameplay() {}

void Gameplay::init(){
	spikes.init(Presenter::m_SCREEN_WIDTH / 3);
	pile.init((float)Presenter::m_SCREEN_WIDTH / 3.0);
	started = false;
	ended = false;
	multiplier = 1;
}

void Gameplay::update() {
	if (!started) {
		if (world.m_inputManager.m_mouseOnClick && pile.collide(world.m_inputManager.m_mouseCoor)) {
			started = true;
			pile.vel.y = 0;
			pile.acc.y = 0;
		}
		return;
	}
	pile.update(world.m_inputManager.keyIsPressed(SDL_SCANCODE_SPACE));

	if (spikes.collide(pile)) {
		ended = true;
		finalScore = pile.score;
	}

	if (spikes.bonbonCollide(pile)) {
		spikes.bonbonActive = false;
		pile.bonboni += multiplier;
		if (pile.bonboni%5 == 0 && pile.bonboni != 0) {
			multiplier++;
		}
	}

	spikes.remakeBonbonIfNess(pile);

	if (pile.justBounced) {
		spikes.makeSpikes(pile.pos.x, pile.vel.x > 0);
	}
}

void Gameplay::draw() {
	drawObject(TextureManager::game_background_texture);
	spikes.draw();
	pile.draw();
	drawObject(TextureManager::gameOverlay_texture);
	drawNum(to_string(pile.score), {600, 250}, 150);
	drawNum(to_string(pile.bonboni), { 1000, 250 }, 100);

	if (multiplier > 1) {
		Drawable multX;
		multX.rect = { 1600, 250, 100, 100 };
		multX.texture = TextureManager::multiplierX_texture;
		drawObject(multX);
		drawNum(to_string(multiplier), { 1720, 250 }, 100);
	}
}


void Gameplay::destruct() {
	spikes.destruct();
	pile.destruct();
}