#ifndef NECORE_NECONTEXT_H_
#define NECORE_NECONTEXT_H_

#include <vector>
#include "assets/AssetsLoader.h"
#include "input/InputBinding.h"

class Window;
class Stage;

class NeContext {
public:
	Window* window;
	Assets assets;
	std::vector<assets_asker_func> askers;
	InputBindings<std::string> bindings;
	Stage* stage = nullptr;
	unsigned long long timer = 0;

	NeContext(Window* window);
	virtual ~NeContext();
};

#endif /* NECORE_NECONTEXT_H_ */
