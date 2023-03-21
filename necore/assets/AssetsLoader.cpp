#include "AssetsLoader.h"

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

void AssetsLoader::performNext(Assets* assets) {
	asset_loading_entry entry = entries.front();
	entries.pop();
	NeResource resource = entry.loader();
	if (resource.data == nullptr) {
		return;
	}
	assets->put(entry.id, resource);
}

void AssetsLoader::performAll(Assets* assets) {
	while (countQueued()) {
		performNext(assets);
	}
}
