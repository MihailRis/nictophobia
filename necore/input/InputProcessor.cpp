#include "InputProcessor.h"
#include "input_constants.h"

InputProcessor::InputProcessor() {
}

InputProcessor::~InputProcessor() {
}

void InputProcessor::markAll() {
}

void InputProcessor::onScroll(int amount){
}

void InputProcessor::onKeyPressed(int keycode, int scancode) {
	keys[keycode] = INPUT_JUST_ACTIVED;
}

void InputProcessor::onKeyRelease(int keycode, int scancode) {
	keys[keycode] = INPUT_JUST_INACTIVED;
}

void InputProcessor::onMousePressed(int button) {
}

void InputProcessor::onMouseRelease(int button) {
}

void InputProcessor::onMouseMove(int x, int y) {
}

void InputProcessor::onWindowResize(int width, int height) {
}
