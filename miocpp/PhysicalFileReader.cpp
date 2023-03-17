#include "PhysicalFileReader.h"

using namespace std;

PhysicalFileReader::PhysicalFileReader(ifstream* file) : file(file) {
	file->seekg(0, file->end);
	length = file->tellg();
	file->seekg(0, file->beg);
}


PhysicalFileReader::~PhysicalFileReader() {
	file->close();
	delete file;
}

size_t PhysicalFileReader::available() {
	return length - file->tellg();
}

int PhysicalFileReader::read() {
	return file->get();
}

size_t PhysicalFileReader::read(char* dst, size_t length) {
	file->read(dst, length);
	return file->gcount();
}
