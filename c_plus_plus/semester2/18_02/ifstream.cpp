#include "ifstream.h"
#include <ostream>

ifs::ifstream::ifstream(const std::string file_name)
        : file(fopen(file_name.c_str(), "r")),
          file_name(file_name) {
    std::cout << "Constructor from string" << std::endl;
    if (!file) {
        throw input_file_exception();
    }
}

ifs::ifstream::ifstream(ifstream &&file_stream)
        : file(nullptr) {
    std::cout << "Move constructor" << std::endl;
    swap(file_stream);
}

ifs::ifstream &ifs::ifstream::operator=(ifstream file_stream) {
    swap(file_stream);
    return *this;
}

ifs::ifstream &ifs::ifstream::operator>>(int &i) {
    fscanf(file, "%d", &i);
    return *this;
}

ifs::ifstream &ifs::ifstream::operator>>(double &d) {
    fscanf(file, "%lf", &d);
    return *this;
}

ifs::ifstream &ifs::ifstream::operator>>(std::string &str) {
    char buffer[255];
    fscanf(file, "%s", buffer);
    str = buffer;
    return *this;
}

bool ifs::ifstream::good() {
    return !fail() && !eof();
}

bool ifs::ifstream::fail() {
    return ferror(file);
}

bool ifs::ifstream::eof() {
    return feof(file);
}

void ifs::ifstream::swap(ifs::ifstream &file_stream) {
    std::swap(file, file_stream.file);

}

ifs::ifstream::~ifstream() {
    std::cout << "Destructor" << std::endl;
    if (file) {
        fclose(file);
    }

}

ifs::ifstream::ifstream(const ifs::ifstream &aConst) {
    std::cout << "Copy constructor" << std::endl;
}
