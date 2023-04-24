#ifndef MIOCPP_IOPATH_H_
#define MIOCPP_IOPATH_H_

#include <string>

class iopath {
	std::string _label;
	std::string _path;
public:
	iopath(std::string data);
	iopath(std::string res, std::string path);

	std::string label() const {
		return _label;
	}

	std::string path() const {
		return _path;
	}

	iopath child(std::string name) const;
	iopath parent() const;
	std::string name() const;
	std::string extension() const;
	std::string nameNoExt() const;

	iopath extended(std::string extension) const;

	std::string toStr() const {
		return _label + ":" + _path;
	}

	std::string readString() const;
	unsigned char* readBytes(size_t* size) const;
	void writeBytes(unsigned char* bytes, size_t size) const;
	bool exists() const;
	bool isFile() const;
	bool isDir() const;
};

#endif /* MIOCPP_IOPATH_H_ */
