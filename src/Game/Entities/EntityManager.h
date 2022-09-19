#pragma once

#include "Block.h"

class EntityManager {

public:

	std::vector<Entity*> entities;
	std::vector<Block*> blocks;
	void tick();
	void render();

};