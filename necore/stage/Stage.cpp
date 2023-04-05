#include "../stage/Stage.h"

#include "../g2d/Sprite.h"


Stage::Stage(){}

Stage::~Stage() {
}

Object* Stage::get(int index) {
	return sprites[index];
}

void Stage::add(Object* sprite) {
	sprites.push_back(sprite);
}
