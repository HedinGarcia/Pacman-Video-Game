#pragma once
#include "Animation.h"
#include "EntityManager.h"
#include "GhostSpawner.h"
enum FACING {
    UP,
    DOWN,
    LEFT,
    RIGHT
};

class Player: public Entity{

    private:
        static int health; //Made variable static in order for any pacman instance to have the same health since there is only one pacman.
        static int score; //Made variable static in order to use it to display it in GameOverState since any instance will have the same score.
        bool canMove;
        int speed = 8;
        bool walking = false;
        FACING facing = DOWN;
        ofImage up, down, left, right;
        Animation *walkUp;
        Animation *walkDown;
        Animation *walkLeft;
        Animation *walkRight;
        EntityManager* em;
        int originalXpos;   //Save pacman's original X position.
        int originalYpos;   //Save pacman's original Y position.
        ofImage lives;      //Save image that resembles pacman's lives.
        vector<ofImage> Currentlives;   //Container of pacman's lives for display.
        GhostSpawner* ghost; //Instance used for flashGhosts function.

    public:
        Player(int, int, int , int, EntityManager*);
        int getHealth(); //Return pacman's health.
        void setHealth(int); //Set pacman's health.
        void displayLives();   //Display pacman's current lives.
        void die();     //Takes one life from pacman and resets his location.
        bool ghostcanDie = false;
        bool canSeeTimer = false;
        int ghostDietimer = 0; //Timer that reaches up to 10 seconds for pacman to kill ghosts.
        bool ghostWasKilled = false;
        int ghost_spawn_countdown = 150; //5 seconds to spawn a ghost after one has died.
        int GhostToSpawn = 0;
        void flashGhosts(); //Establishes the animation of the ghosts to be flashing.
        void originalGhosts(); //Establishes the animation of the ghosts to be the original color.
        bool canFlashGhosts = false;
        int getScore(); //Return player's score.
        void setScore(int); //Set player's score.
        void tick();
        bool spawn_initial_ghosts = true; //Bool that enables spawning 3 extra ghosts at the beginning of the game.
        void render();
        void keyPressed(int);
        void keyReleased(int);
        void damage(Entity* damageSource);
        void mousePressed(int, int, int);
        void reset();
        void setFacing(FACING facing);
        void checkCollisions();
        ofSoundPlayer death;  //Pacman death sound effect.
        ofSoundPlayer eatingGhost; //Pacman eating ghost sound effect.
};