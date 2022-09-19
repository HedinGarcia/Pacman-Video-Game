#pragma once

#include "State.h"
#include "Button.h"
#include "Player.h"

class GameOverState : public State {
private:
	Button *restartButton;
    Player *pacman; //Instance of Pacman in order to set his original health and player score.

public:
	GameOverState();
	void tick();
	void render();
	void keyPressed(int key);
	void mousePressed(int x, int y, int button);
	void reset();
    bool loadMusicOnce = true; //flag for loading game music once in tick.
	ofSoundPlayer gameOverMusic; //ofSoundPlayer instance that will play the gameOverstate sound effect.
	ofSoundPlayer thunder; //ofSoundPlayer used to complement the gameoverstate sound effect.
	ofImage gameOverScreenPhoto; //ofImage instance that will display the photo at the start screen.
	
};