#ifndef NECORE_ASSETS_ASSETSLOADER_H_
#define NECORE_ASSETS_ASSETSLOADER_H_

#include <string>
#include <queue>
#include <unordered_set>
#include <functional>

#include "Assets.h"

class AssetsLoader;

typedef std::function<void(AssetsLoader*)> assets_asker_func;
typedef std::function<NeResource()> resource_loader_func;

struct asset_loading_entry {
	std::string id;
	resource_loader_func loader;
};

class AssetsLoader {
	std::queue<asset_loading_entry> entries;
	std::unordered_set<std::string> names;
public:
	AssetsLoader();
	virtual ~AssetsLoader();

	void queue(assets_asker_func asker);
	void queue(std::string name, resource_loader_func loader);
	size_t countQueued() const {
		return entries.size();
	}

	void performNext(Assets* assets);
	void performAll(Assets* assets);
};

#endif /* NECORE_ASSETS_ASSETSLOADER_H_ */
