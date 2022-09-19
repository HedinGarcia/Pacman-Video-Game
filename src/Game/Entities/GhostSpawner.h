#pragma once
#include "Ghost.h"
#include <vector>
#include <cstdlib>	//Header file to implement srand() and rand() functions.
#include <ctime>	//Header file to implement time() function.
class GhostSpawner : public Ghost
{   
    public: 
        GhostSpawner(int xPos , int yPos, int width, int height, EntityManager* entM, ofImage color);
        GhostSpawner(int xPos , int yPos, int width, int height, string color); //Available colors: red, pink, cyan, and orange
        
        static GhostSpawner* createGhost(){ //Static function that creates a random colored ghost each time is called.
            srand(time(0));
            int i = (rand() % (5)); //Generates a random number between 0.0 and 5.0.
            string color; 
            if (i%4 == 0) {color = "red";}
            else if (i%4 == 1) {color = "pink";}
            else if (i%4 == 2) {color = "cyan";}
            else { color = "orange";}
            GhostSpawner* ghost = new GhostSpawner((ofGetWidth()/2)-8, (ofGetHeight()/2), 16, 16, color);
            return ghost;
        }
};