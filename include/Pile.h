#pragma once

#include "defines.h"

class Pile {
public:
	Pile();
	~Pile();

	float2 pos;
	float2 vel, acc;
	float diam, radius;
	Uint32 lastJump = 0;
	SDL_Texture* texture;

	bool justBounced = false;
	int score = 0, bonboni = 0;

	void init(float x);
	void update(bool jumped);
	void draw();
	void destruct();

	bool collide(float2 pt);
	bool collide(int2 pt);
	bool collide(SDL_Rect r);
private:
	SDL_Rect rect = {-1, -1, -1, -1};
};