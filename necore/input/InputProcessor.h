#ifndef NECORE_INPUTPROCESSOR_H_
#define NECORE_INPUTPROCESSOR_H_

#include <unordered_map>

class InputProcessor {
	std::unordered_map<int, char> keys;
	std::unordered_map<int, char> buttons;
	int scroll = 0;
public:
	int mx = -1;
	int my = -1;
	float dx = 0;
	float dy = 0;
	InputProcessor();
	virtual ~InputProcessor();
	virtual void update();
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

	bool clicked(int button) {
		if (auto status = buttons.find(button); status != keys.end()) {
			return status->second > 0;
		}
		return false;
	}

	int getScroll() const {
		return scroll;
	}
};

#endif /* NECORE_INPUTPROCESSOR_H_ */
