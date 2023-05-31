#include "GLWindow.h"

#include <iostream>
#include <GL/glew.h>
#include <GL/gl.h>
#include <GLFW/glfw3.h>

#include "../input/InputProcessor.h"

std::unordered_map<GLFWwindow*, GLWindow*> GLWindow::wrappers;

void GLWindow::key_callback(GLFWwindow* glfwwindow, int key, int scancode, int action, int) {
	GLWindow* window = GLWindow::wrappers[glfwwindow];
	InputProcessor* processor = window->processor;
	if (action == GLFW_PRESS){
		if (processor) {
			processor->onKeyPressed(key, scancode);
		}
	}
	else if (action == GLFW_RELEASE){
		if (processor) {
			processor->onKeyRelease(key, scancode);
		}
	}
}

void GLWindow::mouse_button_callback(GLFWwindow* glfwwindow, int button, int action, int){
	GLWindow* window = GLWindow::wrappers[glfwwindow];
	InputProcessor* processor = window->processor;
	if (action == GLFW_PRESS){
		if (processor) {
			processor->onMousePressed(button);
		}
	}
	else if (action == GLFW_RELEASE){
		if (processor) {
			processor->onMouseRelease(button);
		}
	}
}

void GLWindow::cursor_position_callback(GLFWwindow* glfwwindow, double xpos, double ypos){
	GLWindow* window = GLWindow::wrappers[glfwwindow];
	InputProcessor* processor = window->processor;
	processor->onMouseMove(xpos, ypos);
}

void GLWindow::window_size_callback(GLFWwindow* glfwwindow, int width, int height){
	GLWindow* window = GLWindow::wrappers[glfwwindow];
	window->width = width;
	window->height = height;
	glViewport(0,0, width, height);
}


GLWindow::GLWindow(GLFWwindow* window, int width, int height)
	: window(window),
	  width(width),
	  height(height) {
}

GLWindow::~GLWindow() {
	glfwMakeContextCurrent(nullptr);
	glfwDestroyWindow(window);
	glfwTerminate();
}

bool GLWindow::shouldClose() {
	return glfwWindowShouldClose(window);
}

void GLWindow::setShouldClose(bool flag) {
	glfwSetWindowShouldClose(window, flag);
}

void GLWindow::swapBuffers() {
	glfwSwapBuffers(window);
}

void GLWindow::swapInterval(int interval) {
	glfwSwapInterval(interval);
}

void GLWindow::pollEvents() {
	processor->update();
	glfwPollEvents();
}

void GLWindow::clear() {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void GLWindow::makeActive() {
	glfwMakeContextCurrent(window);
	glViewport(0,0, width, height);
}

void GLWindow::setCursorVisibility(bool visible) {
	glfwSetInputMode(window, GLFW_CURSOR, visible ? GLFW_CURSOR_NORMAL : GLFW_CURSOR_DISABLED);
}

bool GLWindow::isCursorVisible() {
	return glfwGetInputMode(window, GLFW_CURSOR) == GLFW_CURSOR_NORMAL;
}

void GLWindow::setDepthTest(bool flag) {
	if (flag) {
		glEnable(GL_DEPTH_TEST);
	} else {
		glDisable(GL_DEPTH_TEST);
	}
}

unsigned int GLWindow::getWidth() const {
	return width;
}

unsigned int GLWindow::getHeight() const {
	return height;
}


Window* GLWindow::create(int width, int height, const char* title) {
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_RESIZABLE, GL_TRUE);
	GLFWwindow* window = glfwCreateWindow(width, height, title, nullptr, nullptr);
	if (window == nullptr){
		std::cerr << "Failed to create GLFW Window" << std::endl;
		glfwTerminate();
		return nullptr;
	}
	glfwMakeContextCurrent(window);
	glewExperimental = GL_TRUE;
	if (glewInit() != GLEW_OK){
		std::cerr << "Failed to initialize GLEW" << std::endl;
		glfwTerminate();
		return nullptr;
	}

	glfwSetKeyCallback(window, key_callback);
	glfwSetMouseButtonCallback(window, mouse_button_callback);
	glfwSetCursorPosCallback(window, cursor_position_callback);
	glfwSetWindowSizeCallback(window, window_size_callback);
	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);

	glEnable(GL_BLEND);
	glEnable(GL_DEPTH_TEST);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glEnable(GL_CULL_FACE);

	glfwSwapInterval(1);

	GLWindow* wrapper = new GLWindow(window, width, height);
	GLWindow::wrappers[window] = wrapper;
	return wrapper;
}
