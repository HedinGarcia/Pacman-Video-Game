#include "Ghost.h"

Ghost::Ghost(int xPos , int yPos, int width, int height, EntityManager* entM, ofImage color): Entity( xPos , yPos, width, height){
    sprite.load("images/Background.png");
    ent = entM;

    vector<ofImage> movementFrames;
    ofImage temp;
    
    for(int i=0; i<2; i++){  
        temp.cropFrom(sprite, i*16+456, 64, 16, 16);
        movementFrames.push_back(temp);
    }
    Movement = new Animation(4,movementFrames); //Animation for the first ghost Spawned at the ghost cage initially.
    Orginalcolor = Movement; //Animation that will hold the original color.

    movementFrames.clear(); //Clear vector so it can be used to make the Animation for flashing ghosts when pacman eats a BigDot.
    for(int i=8; i<12; i++){ //Add Colors colors from Dark Blue to Cyan for when the ghost can die. 
        temp.cropFrom(sprite, i*16+456, 64, 16, 16);
        movementFrames.push_back(temp);
    }
    Flashing = new Animation(4,movementFrames); //Second Animation for the ghost when Pacman eats a BigDot.

}

Ghost::Ghost(int xPos , int yPos, int width, int height, string color): Entity(xPos, yPos, width, height){ 
    sprite.load("images/Background.png");
    vector<ofImage> movementFrames;
    ofImage temp;
    if (color == "red"){
        for(int i=0; i<2; i++){   
            temp.cropFrom(sprite, i*16+456, 64, 16, 16);
            movementFrames.push_back(temp);
        }
    }
    if (color == "pink"){
        for(int i=0; i<2; i++){   
            temp.cropFrom(sprite, i*16+456, 80, 16, 16);
            movementFrames.push_back(temp);
        }
    }
    if (color == "cyan"){
        for(int i=0; i<2; i++){ 
            temp.cropFrom(sprite, i*16+456, 96, 16, 16);
            movementFrames.push_back(temp);
        }
    }
    if (color == "orange"){
        for(int i=0; i<2; i++){ 
            temp.cropFrom(sprite, i*16+456, 112, 16, 16);
            movementFrames.push_back(temp);
        }
    }
    Movement = new Animation(4,movementFrames); // Initial Animation, holds first color.
    Orginalcolor = Movement; //Animation that will hold the original color.

    movementFrames.clear(); //Clear vector so it can be used to make the Animation for flashing ghosts when pacman eats a BigDot.
    for(int i=8; i<12; i++){ //Add Colors colors from Dark Blue to Cyan for when the ghost can die. 
        temp.cropFrom(sprite, i*16+456, 64, 16, 16);
        movementFrames.push_back(temp);
    }
    Flashing = new Animation(4,movementFrames); //Second Animation for the ghost when Pacman eats a BigDot.
}

EntityManager* Ghost::ent; //Established static so the same copy that the first Ghost saves will be the same for the rest of the ghosts created in the game. 

void Ghost::flashingAnimation(){ //Animation when pacman eats a BigDot.    
    Movement = Flashing; 
}

void Ghost::originalAnimation(){ //Animation of the original colors of the ghosts.
    Movement= Orginalcolor;
}
void Ghost::tick(){
    stop = false;
    checkCollisions(); //Check if the ghosts have collide with any blocks, if so change direction.
    if(stop == false){
        if(direction == UPWARDS){
            y -= velocity;
            Movement->tick();
        }
        else if(direction == DOWNWARDS){
            y += velocity;
            Movement->tick();
                
        }
        else if(direction == LEFTHAND){
            x -= velocity;
            Movement->tick();
        }
        else if(direction == RIGHTHAND){
            x += velocity;
            Movement->tick();
                
        }
    }
}

void Ghost::render(){ //Draw the animation of Ghost with the current frame.
    ofSetColor(256,256,256);
    if(direction == UPWARDS){
        Movement->getCurrentFrame().draw(x, y, width, height);
    }else if(direction == DOWNWARDS){
        Movement->getCurrentFrame().draw(x, y, width, height);
    }else if(direction == LEFTHAND){
        Movement->getCurrentFrame().draw(x, y, width, height);
    }else if(direction == RIGHTHAND){
        Movement->getCurrentFrame().draw(x, y, width, height);
    }
}

void Ghost::checkCollisions(){
    srand(time(0)); //Using time as a seed to generate random numbers. 
    for(Block* block: ent->blocks){
        switch(direction){
            case UPWARDS:
                if(this->getBounds(x, y-velocity).intersects(block->getBounds())){
                    stop = !stop;
                    if(firstDirection){
                        direction = static_cast<DIRECTION>((rand() % (2))+2); // Random number from 2-3. Move first time to the left or to the right,
                        firstDirection = false;
                    }
                    else{
                        direction = static_cast<DIRECTION>((rand() % 3)+1); // Random number from 1-3. Move either downwards, lefthand or righthand.
                    }
                }
                break;
            case DOWNWARDS:
                if(this->getBounds(x, y+velocity).intersects(block->getBounds())){
                    stop = !stop;
                    holdDirection = (rand() % (3)+1); //Needed in order to determine direction once ghosts collide downwards.
                    (holdDirection == 1)? direction =static_cast<DIRECTION>(0) : direction = static_cast<DIRECTION>(holdDirection); // Random number from set {0,2,3}. Move either upwards, lefthand or righthand.
                }
                break;
            case LEFTHAND:
                if(this->getBounds(x-velocity, y).intersects(block->getBounds())){
                    stop = !stop;
                    holdDirection = (rand() % (3)); //Needed in order to determine direction once ghosts collide to the left.
                    (holdDirection == 2)? direction =static_cast<DIRECTION>(3) : direction = static_cast<DIRECTION>(holdDirection); // Random number from set {0,1,3}. Move either upwards, downwards or righthand.
                }
                break;
            case RIGHTHAND:
                if(this->getBounds(x+velocity, y).intersects(block->getBounds())){
                    stop = !stop;
                    direction = static_cast<DIRECTION>(rand() % 3); // Random number from 0-2. Move either upwards, downwards or lefthand.
                }
                break;
        }
    }   
}