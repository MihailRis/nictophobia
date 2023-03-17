#ifndef MIOCPP_DIRDEVICE_H_
#define MIOCPP_DIRDEVICE_H_

#include "IODevice.h"

#include "FileReader.h"

class DirDevice: public IODevice {
	std::string basepath;
public:
	DirDevice(std::string basepath);
	virtual ~DirDevice();

	virtual FileReader* read(std::string path);
	virtual bool exists(std::string path);
	virtual bool isFile(std::string path);
	virtual bool isDir(std::string path);
};

#endif /* MIOCPP_DIRDEVICE_H_ */
