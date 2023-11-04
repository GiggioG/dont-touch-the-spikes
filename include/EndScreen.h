#pragma once

#include "Button.h"
#include "defines.h"

class EndScreen {
public:
	EndScreen();
	~EndScreen();

	int score, bonboni;
	Button playAgainButton, quitButton;
	bool playAgainClicked = false, quitClicked = false;

	void init(int in_score, int in_bonboni);
	void update();
	void draw();
	void destruct();
};