#pragma once

#include "defines.h"
#include "Pile.h"
#include <utility>
#include <vector>

class Spikes {
public:
	Spikes();
	~Spikes();

	SDL_Rect topLongRect, bottomLongRect;
	vector<pair<SDL_Rect, SDL_Rect>> middle;
	float2 bonbon;
	bool bonbonActive = false;

	void init(int beginX);
	void makeSpikes(int beginX, bool right);
	void remakeBonbonIfNess(const Pile& p);
	void draw();
	void destruct();

	bool collide(Pile& p);
	bool bonbonCollide(Pile& p);
};