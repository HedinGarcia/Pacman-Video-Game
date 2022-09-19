#include "Player.h"
#include "EntityManager.h"
#include "Dot.h"
#include "BigDot.h"

Player::Player(int x, int y, int width, int height, EntityManager* em) : Entity(x, y, width, height){
    originalXpos = this->x;
    originalYpos = this->y;
    sprite.load("images/pacman.png");
    down.cropFrom(sprite, 0, 48, 16, 16);
    up.cropFrom(sprite, 0, 32, 16, 16);
    left.cropFrom(sprite, 0, 16, 16, 16);
    right.cropFrom(sprite, 0, 0, 16, 16);

    
    
    vector<ofImage> downAnimframes;
    vector<ofImage> upAnimframes;
    vector<ofImage> leftAnimframes;
    vector<ofImage> rightAnimframes;
    ofImage temp;
    for(int i=0; i<3; i++){
        temp.cropFrom(sprite, i*16, 48, 16, 16);
        downAnimframes.push_back(temp);
    }
    for(int i=0; i<3; i++){
        temp.cropFrom(sprite, i*16, 32, 16, 16);
        upAnimframes.push_back(temp);
    }
    for(int i=0; i<3; i++){
        temp.cropFrom(sprite, i*16, 16, 16, 16);
        leftAnimframes.push_back(temp);
    }
    for(int i=0; i<3; i++){
        temp.cropFrom(sprite, i*16, 0, 16, 16);
        rightAnimframes.push_back(temp);
    }
    walkDown = new Animation(1,downAnimframes);
    walkUp = new Animation(1,upAnimframes);
    walkLeft = new Animation(1,leftAnimframes);
    walkRight = new Animation(1,rightAnimframes);

    this->em = em;

    death.load("soundEffects/Death.mp3"); //Taken from: Video Game Music https://downloads.khinsider.com/game-soundtracks/album/pac-man-game-sound-effects
    eatingGhost.load("soundEffects/Ghost.mp3"); //Taken from: Video Game Music https://downloads.khinsider.com/game-soundtracks/album/pac-man-game-sound-effects
}

int Player::health = 3; //Setting initially pacman's lives to three. 

int Player::score = 0; //Setting initially player's score to zero. 

int Player::getHealth(){
    return this->health; 
}

void Player::setHealth(int health){
    this->health = health;
}

void Player::displayLives(){   //Displays the lives of Pacman
    Currentlives.clear();
    lives.cropFrom(sprite, 16, 16, 16, 16 ); //This left side view of Pacman represents pacman's lives.
    for(int i=0; i<getHealth(); i++){
        Currentlives.push_back(lives);
    }
    for (int j =0; j<getHealth(); j++){
        Currentlives[j].draw(200+30*j,20,30,30);
    }
    Currentlives.clear();
}

void Player::die(){ //Instance method to reduce pacman's lives by one and reset his location.
    this->health = this->getHealth() - 1 ;
    reset();
}

int Player::getScore(){
    return  this->score;
}

void Player::setScore(int score){
    this->score = score;
}

void Player::tick(){
    canMove = true;
    checkCollisions();
    if(canMove){
        if(facing == UP){
            y-= speed;
            walkUp->tick();
        }else if(facing == DOWN){
            y+=speed;
            walkDown->tick();
        }else if(facing == LEFT){
            x-=speed;
            walkLeft->tick();
        }else if(facing == RIGHT){
            x+=speed;
            walkRight->tick();
        }
    }
    while(spawn_initial_ghosts == true){
        GhostSpawner *ghostPink = new GhostSpawner(312, 150, 16, 16, "pink");
        em->entities.push_back(ghostPink);
        GhostSpawner *ghostCyan = new GhostSpawner(760, 598, 16, 16, "cyan");
        em->entities.push_back(ghostCyan);
        GhostSpawner *ghostOrange = new GhostSpawner(728, 150, 16, 16, "orange");
        em->entities.push_back(ghostOrange);
        spawn_initial_ghosts = false;
    }

    if(ghostcanDie){ //If Pacman has eaten a Big Dot start timer for having the chance to kill ghosts.
        ghostDietimer ++;
        if(ghostDietimer == 300){ //The timer has finished after 10 seconds.
            ghostDietimer =0;
            ghostcanDie = false; //Pacaman cannot kill anymore ghost by now.
            originalGhosts();
        }
    }

    if(ghostWasKilled){ //If a ghost has died start countdown.
        ghost_spawn_countdown --;
        if(GhostToSpawn >1 && ghost_spawn_countdown < 20){ //If multiple ghost were killed before the 5 seconds have passed. 
            em->entities.push_back(GhostSpawner::createGhost());
            ghost_spawn_countdown = 125 ; //Establish a new time, aproxiately 4 seconds, of spawn between the number of ghosts that have been killed before the 5 seconds have ended.
            GhostToSpawn --;
        }
        if(ghost_spawn_countdown == 0){ //The countdown finishes after 5 seconds.   
            em->entities.push_back(GhostSpawner::createGhost()); //Spawn ghost after 5 seconds has passed.
            ghost_spawn_countdown = 150;
            ghostWasKilled =false;
            GhostToSpawn--;
        }
    }
}

void Player::render(){
    ofSetColor(256,256,256);
    // ofDrawRectangle(getBounds());
    if(facing == UP){
        walkUp->getCurrentFrame().draw(x, y, width, height);
    }else if(facing == DOWN){
        walkDown->getCurrentFrame().draw(x, y, width, height);
    }else if(facing == LEFT){
        walkLeft->getCurrentFrame().draw(x, y, width, height);
    }else if(facing == RIGHT){
        walkRight->getCurrentFrame().draw(x, y, width, height);
    }

    ofDrawBitmapString("High Score: " + to_string(getScore()),720, 15); //Display Player's High Score.
    ofDrawBitmapString("Lives: "+ to_string(getHealth()),200, 15); //Display Pacman's lives message with current number of lives.

    if(getHealth()>0){ //Complement pacman's lives display with images.
        displayLives();
    }

    if(canSeeTimer){ //When "t" key is pressed the Ghost can die timer and spawn countdown can be seen.
        if(ghostcanDie){ 
            ofDrawBitmapString("Ghost Can Die Timer: "+ to_string(ghostDietimer),300, 15);
        }

        if(ghostWasKilled){ 
            ofDrawBitmapString("Ghost Spawn Countdown: "+ to_string(ghost_spawn_countdown),500, 15);
        }
    }
}

void Player::keyPressed(int key){
    switch(key){
        case 'w':
            speed = 8 ; //Reestablish speed because once pacman has a direction after reset he will move with the original speed.
            setFacing(UP);
            break;
        case 's':
            speed = 8 ; //Reestablish speed.
            setFacing(DOWN);
            break;
        case 'a':
            speed = 8 ; //Reestablish speed.
            setFacing(LEFT);
            break;
        case 'd':
            speed = 8 ; //Reestablish speed.
            setFacing(RIGHT);
            break;
        case 'r':   //Added key to evaluate reset's functionality.
            reset();
            break;
        case 'n': //Substract a life to Pacman.
            ((this->getHealth() <= 0)?  (this->health = 0) : (this->health = this->getHealth() - 1)); //If true set health to 0, otherwise decrease it.
            break;
        case 'm': //Add a life to Pacman.
            ((this->getHealth() >= 3)? (this->health = 3) : (this->health = this->getHealth() + 1)); //If true set health to 3, otherwise increase it.
            break;
        case 'g': //Spawn a Ghost.
            em->entities.push_back(GhostSpawner::createGhost()); //Add a ghost so it can be treated as an entity and has the ability to kill Pacman. 
            break; 
        case 't': //View Ghost can die timer and Spawn countdown.
            canSeeTimer = !canSeeTimer;
            break; 
    }
}

void Player::keyReleased(int key){
    if(key == 'w' || key =='s' || key == 'a' || key == 'd'){
        walking = false;
    }
}
void Player::mousePressed(int x, int y, int button){

}

void Player::reset(){ //Set pacman's location back to his original one.
    this->x = originalXpos;
    this->y = originalYpos;
    facing = static_cast<FACING>(2); //Face to the left.
    speed = 0 ; //Stop pacman at the original location.
    
}


void Player::setFacing(FACING facing){
    this->facing = facing;
}

void Player::flashGhosts(){ //Function that changes the animations of all the ghosts present to the flash animation. 
    for(Entity* entity:em->entities){
        if(dynamic_cast<GhostSpawner*>(entity)){
            ghost = dynamic_cast<GhostSpawner*>(entity);
            ghost->flashingAnimation();
        }
    }
}

void Player::originalGhosts(){ //Function that changes the animations of all the ghosts present to the orginal color animation.
    for(Entity* entity:em->entities){
        if(dynamic_cast<GhostSpawner*>(entity)){
            ghost = dynamic_cast<GhostSpawner*>(entity);
            ghost->originalAnimation();
        }
    }
}

void Player::checkCollisions(){
    for(Block* block: em->blocks){
        switch(facing){
            case UP:
                if(this->getBounds(x, y-speed).intersects(block->getBounds())){
                    canMove = false;
                }
                break;
            case DOWN:
                if(this->getBounds(x, y+speed).intersects(block->getBounds())){
                    canMove = false;
                }
                break;
            case LEFT:
                if(this->getBounds(x-speed, y).intersects(block->getBounds())){
                    canMove = false;
                }
                break;
            case RIGHT:
                if(this->getBounds(x+speed, y).intersects(block->getBounds())){
                    canMove = false;
                }
                break;
        }
    }
    for(Entity* entity:em->entities){
        if(collides(entity)){
            if(dynamic_cast<Dot*>(entity) || dynamic_cast<BigDot*>(entity)){
                if(dynamic_cast<Dot*>(entity)){
                    score = getScore()+ 5 ; 
                }
                else if(dynamic_cast<BigDot*>(entity)){
                    score = getScore()+ 10 ;
                    flashGhosts();

                    if(ghostDietimer != 0){ //If the timer is running and pacman eats another Bigdot reset the timer for killing ghosts.
                        ghostDietimer = 0;
                    }

                    ghostcanDie = true;
                    
                }
                entity->remove = true;
            }
            else if(dynamic_cast<GhostSpawner*>(entity)){ //If Pacman collides with Ghost without eating a BigDot dies.
                if(ghostDietimer >0 && ghostDietimer <= 300){
                    entity->remove = true; //Remove the ghost because it was killed under the time that pacman had the chance.
                    ghostWasKilled = true;     
                    GhostToSpawn++; //Number of ghosts to spawn.
                    eatingGhost.play(); //Play sound effect when pacman eats a ghost.
                    score = getScore()+ 50 ; //Increase score by 50 points if pacman eats a ghost. 
                }
                else{
                    die();  //Ghosts kill Pacman on collision.
                    death.play(); //Play sound effect when pacman dies.
                }
            }
        }
    }
}