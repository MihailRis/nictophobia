#include "Sprite.h"
#include "../assets/Assets.h"

Sprite::Sprite(glm::vec2 position, glm::vec2 size, glm::vec2 origin)
	: position(position), size(size), origin(origin), rotation(0.0f) {

}

Sprite::~Sprite() {
}

Texture* Sprite::getTexture() const {
	return texture;
}

void Sprite::setTexture(Texture* texture) {
	textureName = "";
	this->texture = texture;
}
