#ifndef NECORE_NECORE_H_
#define NECORE_NECORE_H_

#include <string>
#include <functional>

#include "assets/AssetsLoader.h"

class NeContext;

typedef std::function<int(NeContext*)> build_game_func;
typedef std::function<void(NeContext*)> destruct_game_func;

struct NeGameProject {
	std::string name;
	assets_asker_func assets_ask = nullptr;
	build_game_func build_game = nullptr;
	destruct_game_func destruct_game = nullptr;

	unsigned int init_window_width = 900;
	unsigned int init_window_height = 600;
};

class Necore {
public:
	Necore();
	virtual ~Necore();

	int run(NeGameProject* project);
	void mainloop(NeContext* context);
};

#endif /* NECORE_NECORE_H_ */
