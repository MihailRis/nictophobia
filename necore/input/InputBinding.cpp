#include "InputBinding.h"
#include "input_constants.h"

InputBinding::InputBinding(trigger_func trigger) : trigger(trigger) {
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

void InputBinding::setTrigger(trigger_func trigger) {
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


InputBindings::~InputBindings() {
	for (auto it = bindings.begin(); it != bindings.end(); it++) {
	    delete it->second;
	}
}

void InputBindings::bind(std::string name, trigger_func trigger) {
	auto binding = bindings.find(name);
	if (binding == bindings.end()) {
		bindings[name] = new InputBinding(trigger);
	}
}

void InputBindings::rebind(std::string name, trigger_func trigger) {
	auto binding = bindings.find(name);
	if (binding == bindings.end()) {
		bindings[name] = new InputBinding(trigger);
	} else {
		binding->second->setTrigger(trigger);
	}
}

void InputBindings::unbind(std::string name) {
	auto binding = bindings.find(name);
	if (binding != bindings.end()) {
		bindings.erase(binding);
	}
}

void InputBindings::update() {
	for (auto it = bindings.begin(); it != bindings.end(); it++) {
	    it->second->update();
	}
}

bool InputBindings::isActive(std::string name) {
	auto binding = bindings.find(name);
	if (binding == bindings.end()) {
		return false;
	}
	return binding->second->isActive();
}

bool InputBindings::justActived(std::string name) {
	auto binding = bindings.find(name);
	if (binding == bindings.end()) {
		return false;
	}
	return binding->second->justActived();
}

bool InputBindings::justInactived(std::string name) {
	auto binding = bindings.find(name);
	if (binding == bindings.end()) {
		return false;
	}
	return binding->second->justInactived();
}
