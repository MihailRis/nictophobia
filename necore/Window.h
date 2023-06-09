#ifndef WINDOW_H_
#define WINDOW_H_

class InputProcessor;

class Window {
protected:
	InputProcessor* processor = nullptr;
public:
	Window();
	virtual ~Window();

	virtual bool shouldClose() = 0;

	virtual void setShouldClose(bool flag) = 0;

	virtual void swapBuffers() = 0;

	virtual void swapInterval(int interval) = 0;

	virtual void pollEvents() = 0;

	virtual void makeActive() = 0;

	virtual void setCursorVisibility(bool visible) = 0;

	virtual bool isCursorVisible() = 0;

	virtual void setDepthTest(bool flag) = 0;

	virtual void clear() = 0;

	virtual unsigned int getWidth() const = 0;

	virtual unsigned int getHeight() const = 0;

	virtual void setInputProcessor(InputProcessor* processor) {
		this->processor = processor;
	}

	virtual InputProcessor* getInputProcessor() const {
		return processor;
	}

	float getRatio() const {
		return (float)getWidth()/(float)getHeight();
	}
};

#endif /* WINDOW_H_ */
