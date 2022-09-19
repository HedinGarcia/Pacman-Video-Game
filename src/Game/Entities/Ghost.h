#pragma once
#include "Entity.h"
#include "EntityManager.h"
#include "Animation.h"
#include <cstdlib>	//Header file to implement srand() and rand() functions.
#include <ctime>	//Header file to implement time() function.


enum DIRECTION{ //Enum variables to represent direction of the ghosts.
    UPWARDS = 0, 
    DOWNWARDS,
    LEFTHAND,
    RIGHTHAND

};
class Ghost: public Entity{
    private:
        int velocity = 4;   
        static EntityManager* ent; //Entity instance in order to use in checking collision between ghosts and blocks.
        DIRECTION direction = UPWARDS;
        bool stop= false;
        Animation* Flashing; //Animation for ghosts when Pacman eats a BigDot.
        Animation* Movement; //Initial animation.
        Animation* Orginalcolor; //Animation for ghosts' orginal color.
    public:
        Ghost(int xPos , int yPos, int width, int height, EntityManager* entM, ofImage color);
        Ghost(int xPos , int yPos, int width, int height, string color); //Available colors: red, pink, cyan, and orange
        //void setSprite(ofImage sprite) { this->sprite = sprite;}
        void flashingAnimation(); //Flashing animations for when Pacman eats a BigDot.
        void originalAnimation(); //Original animation to return to when the ghosts finish flashing.
        void tick();    //Update ghosts movement troughout the game.
        void render();
        void checkCollisions(); //Check if collide with any blocks, if so change its direction.
        bool firstDirection = true; //First direction in order for the ghosts not to get stuck in the cage.
        int holdDirection; //Variable that is used in a condition before assigning it to a direction.

};