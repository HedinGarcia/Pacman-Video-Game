#include "MenuState.h"

MenuState::MenuState() {
	startButton = new Button((ofGetWidth()/2)-50, ofGetHeight()/2 + 100, 50, 50, "Start");
	menuMusic.load("Pac-Man World - Title Screen and Main Menu.mp3"); //Taken from Ultimate Justin:https://www.youtube.com/watch?v=94qHPiYm6Ts&list=PL6BC6A1F6A3887333
	menuMusic.play(); //Inside the menu state play menu music.
	menuMusic.setLoop(true);

	startScreenPhoto.load("images/startScreenImage.png"); //Taken from: Rafael García, https://geekzilla.tech/home/wp-content/uploads/2019/11/pac-man.jpg
	startScreenPhoto.resize(ofGetWidth()/4, ofGetHeight()/4); //Check aspect ratio
}
void MenuState::tick() {
	startButton->tick();
	if(startButton->wasPressed()){
		setNextState("Game");
		setFinished(true);
		menuMusic.stop();	//Inside the game state stop menu music.

	}
}
void MenuState::render() {
	ofSetBackgroundColor(0); //Changed to black
	startButton->render();
	startScreenPhoto.draw((ofGetWidth()/2)-140, (ofGetHeight()/8)+40);	
}

void MenuState::keyPressed(int key){
	
}

void MenuState::mousePressed(int x, int y, int button){
	startButton->mousePressed(x, y);
}

void MenuState::reset(){
	setFinished(false);
	setNextState("");
	startButton->reset();
}