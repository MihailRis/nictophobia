#include "InputProcessor.h"
#include "input_constants.h"

InputProcessor::InputProcessor() {
}

InputProcessor::~InputProcessor() {
}

void InputProcessor::markAll() {
}

void InputProcessor::onScroll(int amount){
	scroll = amount;
}

void InputProcessor::onKeyPressed(int keycode, int) {
	keys[keycode] = INPUT_JUST_ACTIVED;
}

void InputProcessor::onKeyRelease(int keycode, int) {
	keys[keycode] = INPUT_JUST_INACTIVED;
}

void InputProcessor::onMousePressed(int button) {
	buttons[button] = INPUT_JUST_ACTIVED;
}

void InputProcessor::onMouseRelease(int button) {
	buttons[button] = INPUT_JUST_INACTIVED;
}

void InputProcessor::onMouseMove(int, int) {
}

void InputProcessor::onWindowResize(int, int) {
}
