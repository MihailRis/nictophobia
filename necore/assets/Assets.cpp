#include "Assets.h"

Assets::Assets() {

}

Assets::~Assets() {
	for (auto it = assets.begin(); it != assets.end(); it++) {
		Asset asset = it->second;
		if (asset.resource.destructor) {
			asset.resource.destructor(asset.resource.data);
		}
		asset.resource.data = nullptr;
	}

}

