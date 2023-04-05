#ifndef NECORE_NECORE_H_
#define NECORE_NECORE_H_

#include <functional>

#include "assets/AssetsLoader.h"

class NeContext;

typedef std::function<int(NeContext*)> build_game_func;
typedef std::function<void(NeContext*)> destruct_game_func;

class Necore {
public:
	Necore();
	virtual ~Necore();

	int run(assets_asker_func assets_ask,
			build_game_func build_game,
			destruct_game_func destruct_game,
			const char* window_title);
	void mainloop(NeContext* context);
};

#endif /* NECORE_NECORE_H_ */
