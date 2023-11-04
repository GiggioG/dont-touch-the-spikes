#pragma once

#include "defines.h"
#include "Pile.h"
#include "Button.h"
#include "Spikes.h"

class Gameplay {
public:
	Gameplay();
	~Gameplay();

	bool started = false;
	Spikes spikes;
	Pile pile;
	int finalScore;
	bool ended;
	int multiplier = 1;

	void init();
	void update();
	void draw();
	void destruct();
};