#ifndef NECORE_GLWINDOW_H_
#define NECORE_GLWINDOW_H_

#include "../Window.h"
#include <unordered_map>

class GLFWwindow;

class GLWindow : public Window {
	GLFWwindow* window;
	int width;
	int height;

	static void key_callback(GLFWwindow* glfwwindow, int key, int scancode, int action, int mode);
	static void mouse_button_callback(GLFWwindow* glfwwindow, int button, int action, int mode);
	static void cursor_position_callback(GLFWwindow* glfwwindow, double xpos, double ypos);
	static void window_size_callback(GLFWwindow* glfwwindow, int width, int height);
public:
	static std::unordered_map<GLFWwindow*, GLWindow*> wrappers;

	GLWindow(GLFWwindow* window, int width, int height);

	virtual ~GLWindow();

	bool shouldClose();

	void swapBuffers();

	void swapInterval(int interval);

	void pollEvents();

	void clear();

	void makeActive();

	void setCursorVisibility(bool visible);

	bool isCursorVisible();

	static Window* create(int width, int height, const char* title);
};

#endif /* NECORE_GLWINDOW_H_ */
