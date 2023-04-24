#ifndef MIOCPP_MIO_H_
#define MIOCPP_MIO_H_

#include <string>
#include <unordered_map>
#include "IODevice.h"
#include "iopath.h"

namespace mio {
	namespace {
		std::unordered_map<std::string, IODevice*> devices;
	}

	void add_device(std::string label, IODevice* device);

	IODevice* get_device(std::string label);

	IODevice* pop_device(std::string label);

	std::string readString(const iopath* path);

	unsigned char* readBytes(const iopath* path, size_t* size);

	void writeBytes(const iopath* path, unsigned char* bytes, size_t size);

	bool exists(const iopath* path);
	bool isFile(const iopath* path);
	bool isDir(const iopath* path);
}


#endif /* MIOCPP_MIO_H_ */
