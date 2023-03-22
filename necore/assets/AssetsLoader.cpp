#include "AssetsLoader.h"

#include <iostream>

AssetsLoader::AssetsLoader() {

}

AssetsLoader::~AssetsLoader() {

}


void AssetsLoader::queue(assets_asker_func asker) {

}

void AssetsLoader::queue(std::string name, resource_loader_func loader) {
	if (names.find(name) != names.end()){
		return;
	}
	entries.push({name, loader});
}

int AssetsLoader::performNext(Assets* assets) {
	asset_loading_entry entry = entries.front();
	entries.pop();
	std::cout << "assets loading: " << entry.id << std::endl;
	NeResource resource = entry.loader();
	if (resource.data == nullptr) {
		return 1;
	}
	assets->put(entry.id, resource);
	return 0;
}

int AssetsLoader::performAll(Assets* assets) {
	while (countQueued()) {
		int status = performNext(assets);
		if (status) {
			return status;
		}
	}
	return 0;
}
