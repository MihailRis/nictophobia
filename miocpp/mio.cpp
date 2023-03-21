#include "mio.h"
#include <iostream>

void mio::add_device(std::string label, IODevice* device) {
	devices[label] = device;
}

IODevice* mio::get_device(std::string label) {
	IODevice* device = devices[label];
	if (device == nullptr) {
		std::cerr << "no device '" << label << "' found" << std::endl;
	}
	return device;
}

IODevice* mio::pop_device(std::string label) {
	IODevice* device = devices[label];
	if (device == nullptr) {
		std::cerr << "no device '" << label << "' found" << std::endl;
	} else {
		auto iter = devices.find(label);
		devices.erase(iter);
	}
	return device;
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
