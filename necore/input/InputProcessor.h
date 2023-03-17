#ifndef NECORE_INPUTPROCESSOR_H_
#define NECORE_INPUTPROCESSOR_H_

#include <unordered_map>

class InputProcessor {
	std::unordered_map<int, char> keys;
public:
	InputProcessor();
	virtual ~InputProcessor();
	virtual void markAll();
	virtual void onScroll(int amount);
	virtual void onKeyPressed(int keycode, int scancode);
	virtual void onKeyRelease(int keycode, int scancode);
	virtual void onMousePressed(int button);
	virtual void onMouseRelease(int button);
	virtual void onMouseMove(int x, int y);
	virtual void onWindowResize(int width, int height);

	bool pressed(int keycode) {
		if (auto status = keys.find(keycode); status != keys.end()) {
			return status->second > 0;
		}
		return false;
	}
};

#endif /* NECORE_INPUTPROCESSOR_H_ */
