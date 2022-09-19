#include "Map.h"

Map::Map(EntityManager* em){
    entityManager = em;
}

void Map::tick(){
	entityManager->tick();
	player->tick();

}
void Map::render(){
    ofSetBackgroundColor(0, 0, 0);
	entityManager->render();
	player->render();
	if(ghostspawner->remove != true){
		ghostspawner->render();
	}

}

void Map::keyPressed(int key){
	player->keyPressed(key);
}

void Map::mousePressed(int x, int y, int button){
	player->mousePressed(x, y, button);
}

void Map::keyReleased(int key){
	player->keyReleased(key);
}
void Map::addBlock(Block* e){
    entityManager->blocks.push_back(e);
}
void Map::addEntity(Entity* e){
	entityManager->entities.push_back(e);
}
void Map::setPlayer(Player* p){
    player = p;
}
void Map::setGhostSpawner(GhostSpawner* g){
    ghostspawner = g;
	entityManager->entities.push_back(g);
}

