#include "FileReader.h"

FileReader::~FileReader() {
}

void FileReader::readFully(char* buffer, size_t length) {
    size_t red;
    for (size_t pos = 0; pos < length; pos += red) {
        red = read(buffer+pos, length - pos);
        if (red < 0) {
            return;
        }
    }
}
