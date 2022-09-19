#include "GameOverState.h"

GameOverState::GameOverState() {
	restartButton = new Button((ofGetWidth()/2)-50, ofGetHeight()/2 + 75, 50, 50, "Restart");
    gameOverMusic.load("Game_Over_Music.mp3"); //Taken from: Sound EffectTrans https://www.youtube.com/watch?v=to_w8JtlYJs
	thunder.load("soundEffects/Thunder.mp3"); //Taken from:MrSountabel https://www.youtube.com/watch?v=T-BOPr7NXME
	gameOverScreenPhoto.load("images/pacman-logo.png"); //https://www.vhv.rs/viewpic/hwTbxwb_pac-man-logo-logo-de-pac-man-hd/
	gameOverScreenPhoto.resize(ofGetWidth()/3, ofGetHeight()/4); 	
}
	
void GameOverState::tick() {
	restartButton->tick();

    while(loadMusicOnce) { //Loop the menu music once.
	    gameOverMusic.play(); //Inside the menu state play menu music.
		thunder.play();
	    gameOverMusic.setLoop(true);
		thunder.setLoop(true);
		loadMusicOnce = false;
	}
	if(restartButton->wasPressed()){
        pacman->setHealth(3); //Once the restart button is pressed, Pacman will have it's original health.
        pacman->setScore(0);  //Once the restart button is pressed, the player will have it's original score.
		setNextState("Game");
		setFinished(true);
		gameOverMusic.stop();	//Inside the game state stop menu music.
		thunder.stop(); //Inside the game state stop menu music.
        loadMusicOnce = true; //Set the variable true so it can play music once this State is set to currentState again.
	}
}
void GameOverState::render() {
	ofSetBackgroundColor(0); 
	restartButton->render();
	gameOverScreenPhoto.draw((ofGetWidth()/2)-165, (ofGetHeight()/8)+40);
	ofSetColor(255, 255, 0);
	ofDrawBitmapString("Game Over",(ofGetWidth()/2)-60, (ofGetHeight()/8)-30);
	ofDrawBitmapString("High Score: " + to_string(pacman->getScore()),(ofGetWidth()/2)-80, (ofGetHeight()/8)); //Display Player's High Score.
	ofDrawBitmapString("Project developed by: Hedin Garcia and William Negron.", (ofGetWidth()/2)-200, ofGetHeight()/2 + 150);
	ofDrawBitmapString("Menu State Music by: Ultimate Justin.\nMenu State Photo by: Rafael Garcia.\nGame State Music by: TheCantinaBand.\nGame State Sound Effect, Pacman Dying by: Video Game Music\nGame State Sound Effect, Pacman Eating Ghost by: Video Game Music\nGame Over State Music by: Sound EffectTrans.\nGame Over State Thunder Sound Effect by: MrSountabel\nGame Over State Photo by: vhv.rs", (ofGetWidth()/2)-200, ofGetHeight()/2 + 175);
}

void GameOverState::keyPressed(int key){
	
}

void GameOverState::mousePressed(int x, int y, int button){
	restartButton->mousePressed(x, y);
}

void GameOverState::reset(){
	setFinished(false);
	setNextState("");
	restartButton->reset();
}