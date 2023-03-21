#ifndef NECORE_ASSETS_ASSETS_H_
#define NECORE_ASSETS_ASSETS_H_

#include <string>
#include <unordered_map>
#include <functional>

enum NeResourceType {
	UNHANDLED,
	SIMPLE,
	ARRAY,
};

typedef std::function<void(void*)> resource_destructor_func;

struct NeResource {
	NeResourceType type;
	void* data;
	resource_destructor_func destructor = nullptr;
	NeResource() : type(UNHANDLED), data(nullptr) {}
	NeResource(NeResourceType type, void*data) : type(type), data(data) {}
	NeResource(NeResourceType type, void*data, resource_destructor_func destructor)
	: type(type), data(data), destructor(destructor) {}
};

struct Asset {
	NeResource resource;
};

class Assets {
	std::unordered_map<std::string, Asset> assets;
public:
	Assets();
	virtual ~Assets();

	void* get(std::string id) {
		return assets[id].resource.data;
	}

	void put(std::string id, NeResource resource) {
		assets[id] = {resource};
	}
};

#endif /* NECORE_ASSETS_ASSETS_H_ */
