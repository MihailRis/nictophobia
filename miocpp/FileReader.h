#ifndef MIOCPP_FILEREADER_H_
#define MIOCPP_FILEREADER_H_

#include <stdlib.h>

class FileReader {
public:
	virtual ~FileReader();
	virtual size_t available() = 0;
	virtual int read() = 0;
	virtual size_t read(char* dst, size_t length) = 0;

	virtual void readFully(char* buffer, size_t length);
};

#endif /* MIOCPP_FILEREADER_H_ */
