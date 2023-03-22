#ifndef NECORE_G2D_SPRITE_H_
#define NECORE_G2D_SPRITE_H_

#include <string>
#include <glm/glm.hpp>

#include "../uvregion.h"

class Texture;
class Assets;

class Sprite {
	std::string textureName = "";
	Texture* texture = nullptr;
	glm::vec2 position;
	glm::vec2 size;
	glm::vec2 origin;
	glm::vec4 color {1.0f, 1.0f, 1.0f, 1.0f};
	uvregion region {0.0f, 0.0f, 1.0f, 1.0f};
	float rotation;
public:
	bool flippedX = false;
	bool flippedY = false;

	Sprite(glm::vec2 position, glm::vec2 size, glm::vec2 origin);
	virtual ~Sprite();

	Texture* getTexture() const;
	std::string getTextureName() const {
		return textureName;
	}

	void setTexture(Texture* texture);
	void setTexture(std::string name) {
		this->textureName = name;
	}

	float getRotation() const {
		return rotation;
	}

	void setPosition(glm::vec2 vector) {
		position = vector;
	}

	void setSize(glm::vec2 vector) {
		size = vector;
	}

	void setOrigin(glm::vec2 vector) {
		origin = vector;
	}

	glm::vec2 getPosition() const {
		return position;
	}

	glm::vec2 getSize() const {
		return size;
	}

	glm::vec2 getOrigin() const {
		return origin;
	}

	glm::vec4 getColor() const {
		return color;
	}

	uvregion getRegion() const {
		return region;
	}
};

#endif /* NECORE_G2D_SPRITE_H_ */
