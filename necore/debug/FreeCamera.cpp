#include "FreeCamera.h"

#include "../Window.h"
#include "../Camera.h"
#include "../NeContext.h"
#include "../input/InputProcessor.h"

void FreeCamera::setCamera(Camera* camera) {
	this->camera = camera;
}


void FreeCamera::update(NeContext* context) {
	if (camera == nullptr) {
		return;
	}
	Window* window = context->window;
	if (!window->isCursorVisible()) {
		mx -= window->getInputProcessor()->dy/(float)window->getHeight();
		my -= window->getInputProcessor()->dx/(float)window->getHeight();
		camera->setRotation(glm::mat4(1.0f));
		camera->rotate(mx, my, 0);
	}
	glm::vec3 motion {0.0f, 0.0f, 0.0f};
	float speed = 0.3f;
	glm::vec3 front = camera->getFront();
	glm::vec3 right = camera->getRight();
	glm::vec3 up = camera->getUp();
	if (context->bindings.isActive("core:up")) {motion += front*speed;};
	if (context->bindings.isActive("core:down")) {motion -= front*speed;};
	if (context->bindings.isActive("core:left")) {motion -= right*speed;};
	if (context->bindings.isActive("core:right")) {motion += right*speed;};
	if (context->bindings.isActive("core:elevate")) {motion += up*speed;};
	if (context->bindings.isActive("core:lower")) {motion -= up*speed;};
	camera->translate(motion);
}
