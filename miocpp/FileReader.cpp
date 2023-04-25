#include "FileReader.h"
#include <stdlib.h>

FileReader::~FileReader() {
}

void FileReader::readFully(char* buffer, size_t length) {
    int red;
    for (size_t pos = 0; pos < length; pos += red) {
        red = read(buffer+pos, length - pos);
        if (red < 0) {
            return;
        }
    }
}
