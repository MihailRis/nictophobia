#include "InputBinding.h"
#include "input_constants.h"

InputBinding::InputBinding(std::function<bool()> trigger) : trigger(trigger) {
}

void InputBinding::update() {
	bool active = trigger();
	if (active) {
		if (status == INPUT_INACTIVE || status == INPUT_JUST_INACTIVED) {
			status = INPUT_JUST_ACTIVED;
		}
		else {
			status = INPUT_ACTIVE;
		}
	} else {
		if (status == INPUT_ACTIVE || status == INPUT_JUST_ACTIVED) {
			status = INPUT_JUST_INACTIVED;
		}
		else {
			status = INPUT_INACTIVE;
		}
	}
}

void InputBinding::setTrigger(std::function<bool()> trigger) {
	this->trigger = trigger;
}

bool InputBinding::isActive() const {
	return status > 0;
}

bool InputBinding::justActived() const {
	return status == INPUT_JUST_ACTIVED;
}

bool InputBinding::justInactived() const {
	return status == INPUT_JUST_INACTIVED;
}
