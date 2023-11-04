#include "Presenter.h"
#include "ConfigManager.h"
#include "TextureManager.h"
#include "Pile.h"

extern ConfigManager* cfgm;

Pile::Pile() {}
Pile::~Pile() {}

float GRAVITY, JUMP;
Uint32 jumpCooldownMilis;

void Pile::init(float x){
	GRAVITY = cfgm->cfg["GRAVITY"].f;
	JUMP = cfgm->cfg["JUMP"].f;
	jumpCooldownMilis = cfgm->cfg["JUMP_COOLDOWN_MILIS"].i;

	score = 0;
	bonboni = 0;
	lastJump = 0;

	diam = cfgm->cfg["PILE_DIAMETER"].i;
	radius = diam / 2;
	pos.x = x;
	pos.y = (float)Presenter::m_SCREEN_HEIGHT / 2;

	texture = TextureManager::pile1_texture;

	vel.x = cfgm->cfg["HORIZ_VEL"].f;
}

void Pile::update(bool jumped) {
	acc.x = 0;
	acc.y = GRAVITY;
	if (jumped) {
		Uint32 now = SDL_GetTicks();
		if ((now - lastJump) > jumpCooldownMilis) {
			vel.y = JUMP;
			acc.y = JUMP;
			lastJump = now;
		}
	}

	vel.x += acc.x;
	vel.y += acc.y;

	pos.x += vel.x;
	pos.y += vel.y;

	if (pos.y > Presenter::m_SCREEN_HEIGHT - radius) {
		pos.y = Presenter::m_SCREEN_HEIGHT - radius;
	}else if (pos.y < radius) {
		pos.y = radius;
	}

	justBounced = false;

	if (pos.x > Presenter::m_SCREEN_WIDTH - radius) {
		pos.x = Presenter::m_SCREEN_WIDTH - radius;
		vel.x *= -1;
		justBounced = true;
		score++;
	} else if (pos.x < radius) {
		pos.x = radius;
		vel.x *= -1;
		justBounced = true;
		score++;
	}
}

void Pile::draw() {
	rect.w = diam;
	rect.h = diam;
	rect.x = pos.x - (float)rect.w / 2;
	rect.y = pos.y - (float)rect.h / 2;
	Drawable d;
	d.rect = rect;
	d.texture = texture;
	if (vel.x < 0) { d.flip = SDL_FLIP_HORIZONTAL; }
	drawObject(d);
}

void Pile::destruct() {
	
}

bool Pile::collide(float2 pt) {
	float dx = pt.x - pos.x;
	float dy = pt.y - pos.y;
	float dist = dx * dx + dy * dy;
	return dist <= radius*radius;
}

bool Pile::collide(int2 pt){
	float2 fpt = { pt.x, pt.y };
	return collide(fpt);
}

float clamp(float val, float min, float max) {
	if (val < min) { return min; }
	if (val > max) { return max; }
	return val;
}

bool Pile::collide(SDL_Rect r){
	float closestX = clamp(pos.x, r.x, r.x+r.w);
	float closestY = clamp(pos.y, r.y, r.y+r.h);

	float dx = closestX - pos.x;
	float dy = closestY - pos.y;

	float dist2 = dx * dx + dy * dy;
	return dist2 <= radius * radius;
}
