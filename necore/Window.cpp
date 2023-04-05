#include "Window.h"
#include "input/InputProcessor.h"

Window::Window() {
	processor = new InputProcessor();
}

Window::~Window(){
	delete processor;
}
