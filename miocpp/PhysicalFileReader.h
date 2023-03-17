#ifndef MIOCPP_PHYSICALFILEREADER_H_
#define MIOCPP_PHYSICALFILEREADER_H_

#include "FileReader.h"

#include <stdlib.h>
#include <fstream>

class PhysicalFileReader: public FileReader {
	std::ifstream* file;
	size_t length;
public:
	PhysicalFileReader(std::ifstream* stream);
	virtual ~PhysicalFileReader();

	virtual size_t available();
	virtual int read();
	virtual size_t read(char* dst, size_t length);
};

#endif /* MIOCPP_PHYSICALFILEREADER_H_ */
