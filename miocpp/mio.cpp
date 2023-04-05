#include "mio.h"
#include <iostream>

void mio::add_device(std::string label, IODevice* device) {
	devices[label] = device;
}

IODevice* mio::get_device(std::string label) {
	auto found = devices.find(label);
	if (found == devices.end()) {
		std::cerr << "no device '" << label << "' found" << std::endl;
	}
	return found->second;
}

IODevice* mio::pop_device(std::string label) {
	auto found = devices.find(label);
	if (found == devices.end()) {
		std::cerr << "no device '" << label << "' found" << std::endl;
	} else {
		IODevice* device = found->second;
		devices.erase(found);
		return device;
	}
	return nullptr;
}

std::string mio::readString(const iopath* path) {
	if (IODevice* device = get_device(path->label())) {
		return device->readString(path->path());
	}
	return "";
}

unsigned char* mio::readBytes(const iopath* path, size_t* size) {
	if (IODevice* device = get_device(path->label())) {
		return device->readBytes(path->path(), size);
	}
	return nullptr;
}

bool mio::exists(const iopath* path) {
	if (IODevice* device = get_device(path->label())) {
		return device->exists(path->path());
	}
	return false;
}

bool mio::isFile(const iopath* path) {
	if (IODevice* device = get_device(path->label())) {
		return device->isFile(path->path());
	}
	return false;
}

bool mio::isDir(const iopath* path) {
	if (IODevice* device = get_device(path->label())) {
		return device->isDir(path->path());
	}
	return false;
}
