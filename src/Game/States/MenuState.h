#pragma once

#include "State.h"
#include "Button.h"

class MenuState : public State {
private:
	Button *startButton;

public:
	MenuState();
	void tick();
	void render();
	void keyPressed(int key);
	void mousePressed(int x, int y, int button);
	void reset();
	ofSoundPlayer menuMusic; //ofSoundPlayer instance that will play the menu music.
	ofImage startScreenPhoto; //ofImage instance that will display the photo at the start screen
	
};
