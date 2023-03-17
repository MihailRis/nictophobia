#ifndef NECORE_INPUT_INPUTBINDING_H_
#define NECORE_INPUT_INPUTBINDING_H_

#include <unordered_map>
#include <functional>

typedef std::function<bool()> trigger_func;

class InputBinding {
	trigger_func trigger;
	char status = 0;
public:
	InputBinding(trigger_func trigger);

	void update();
	void setTrigger(trigger_func trigger);

	bool isActive() const;
	bool justActived() const;
	bool justInactived() const;
};

class InputBindings {
	std::unordered_map<std::string, InputBinding*> bindings;
public:
	virtual ~InputBindings();
	void bind(std::string name, trigger_func trigger);
	void rebind(std::string name, trigger_func trigger);
	void unbind(std::string name);
	void update();

	bool isActive(std::string name);
	bool justActived(std::string name);
	bool justInactived(std::string name);
};

#endif /* NECORE_INPUT_INPUTBINDING_H_ */
