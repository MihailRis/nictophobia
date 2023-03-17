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

template <typename T>
class InputBindings {
	std::unordered_map<T, InputBinding*> bindings;
public:
	virtual ~InputBindings();
	void bind(T name, trigger_func trigger);
	void rebind(T name, trigger_func trigger);
	void unbind(T name);
	void update();

	bool isActive(T name);
	bool justActived(T name);
	bool justInactived(T name);
};
template class InputBindings<int>;
template class InputBindings<std::string>;

#endif /* NECORE_INPUT_INPUTBINDING_H_ */
