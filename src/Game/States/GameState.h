#pragma once
#include "State.h"
#include "Player.h"
#include "MapBuilder.h"

class GameState: public State{
    public: 
        GameState();
		void reset();
		void tick();
		void render();
		void keyPressed(int key);
		void mousePressed(int x, int y, int button);
		void keyReleased(int key);
		ofSoundPlayer gameMusic; //ofSoundPlayer instance that will play the game music.
		bool loadMusicOnce = true; //flag for loading game music once in tick.
		bool restartMap = false; //Restart the map so the player can play as many times as it wants.
	private:
		ofImage mapImage;
		Map* map;
		Player* pacman; //Instance of Pacman in order to get his health and determine if he has lost all of its lives.
};