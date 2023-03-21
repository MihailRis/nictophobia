#ifndef MIOCPP_IODEVICE_H_
#define MIOCPP_IODEVICE_H_

#include <iostream>
#include <string>

class FileReader;

class IODevice {
public:
	virtual ~IODevice();
	virtual FileReader* read(std::string path) = 0;
	virtual bool exists(std::string path) = 0;
	virtual bool isFile(std::string path) = 0;
	virtual bool isDir(std::string path) = 0;

	virtual std::string readString(std::string path);
	virtual unsigned char* readBytes(std::string path, size_t* length);
};

#endif /* MIOCPP_IODEVICE_H_ */
