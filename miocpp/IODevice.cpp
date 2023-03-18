#include "IODevice.h"

#include "FileReader.h"

IODevice::~IODevice() {
}

std::string IODevice::readString(std::string path) {
	FileReader* reader = read(path);
	if (reader == nullptr)
		return "";
	size_t length = reader->available();
	char* buffer = new char[length];
	reader->readFully(buffer, length);
	delete reader;
	std::string s(buffer, length);
	delete[] buffer;
	return s;
}

unsigned char* IODevice::readBytes(std::string path, size_t& length) {
	FileReader* reader = read(path);
	if (reader == nullptr)
		return nullptr;
	length = reader->available();
	unsigned char* buffer = new unsigned char[length];
	reader->readFully((char*)buffer, length);
	delete reader;
	return buffer;
}
