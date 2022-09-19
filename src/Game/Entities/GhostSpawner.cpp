#include "GhostSpawner.h"

GhostSpawner::GhostSpawner(int xPos , int yPos, int width, int height, EntityManager* entM, ofImage color): Ghost( xPos , yPos, width, height , entM , color){}

GhostSpawner::GhostSpawner(int xPos , int yPos, int width, int height, string color): Ghost( xPos , yPos, width, height , color){}
