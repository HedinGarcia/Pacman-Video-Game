#include "GameState.h"
#include "Entity.h"

GameState::GameState() {
	mapImage.load("images/map1.png");
	map = MapBuilder().createMap(mapImage);
	gameMusic.load("PacMan Original Theme.mp3"); // Load music for GameState. Taken from TheCantinaBand:https://www.youtube.com/watch?v=BxYzjjs6d1s 
}
void GameState::tick() {
	map->tick();
	while(restartMap == true){
		delete map; //Delete previous map and generate a new one.
		map = MapBuilder().createMap(mapImage);
		restartMap = !restartMap; //Set to false so it can be set to true when changed to GameOverState.
	}
	while(loadMusicOnce) { //Loop the game music once.
		gameMusic.play();
		gameMusic.setLoop(true);
		loadMusicOnce = false;
	}
	if(pacman->getHealth() == 0){ //Once Pacman has died change to GameOverState
		setNextState("GameOver"); 
		setFinished(true);
		gameMusic.stop();
		loadMusicOnce = true; //Set the variable true so it can play music once this State is set to currentState again.
		restartMap = !restartMap; //Set true so when changing from GameOverState to GameState a new map is set.
	}
}
void GameState::render() {
	map->render();
}

void GameState::keyPressed(int key){
	map->keyPressed(key);
}

void GameState::mousePressed(int x, int y, int button){
	map->mousePressed(x, y, button);
}

void GameState::keyReleased(int key){
	map->keyReleased(key);
}

void GameState::reset(){
	setFinished(false);
	setNextState("");
}