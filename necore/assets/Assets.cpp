#include "Assets.h"

#include <iostream>

Assets::Assets() {

}

Assets::~Assets() {
	std::cout << "cleaning up assets" << std::endl;
	for (auto it = assets.begin(); it != assets.end(); it++) {
		Asset asset = it->second;
		std::cout << "- " << it->first << std::endl;
		if (asset.resource.destructor) {
			asset.resource.destructor(asset.resource.data);
		}
		asset.resource.data = nullptr;
	}

}

