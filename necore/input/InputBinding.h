#ifndef NECORE_INPUT_INPUTBINDING_H_
#define NECORE_INPUT_INPUTBINDING_H_

#include <functional>

class InputBinding {
	std::function<bool()> trigger;
	char status = 0;
public:
	InputBinding(std::function<bool()> trigger);

	void update();
	void setTrigger(std::function<bool()> trigger);

	bool isActive() const;
	bool justActived() const;
	bool justInactived() const;
};

#endif /* NECORE_INPUT_INPUTBINDING_H_ */
