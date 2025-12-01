#include "FileReader.h"
#include <stdexcept>

void FileReader::checkFileIsOpen() const {
    if (file == nullptr || !file->is_open()) {
        throw std::runtime_error("File is not open: " + filename);
    }
}

void FileReader::cleanup() {
    if (file != nullptr) {
        file->close();
        delete file;
        file = nullptr;
    }
}

FileReader::FileReader(const std::string& filename) 
    : filename(filename), file(nullptr) {}

FileReader::~FileReader() {
    cleanup();
}

void FileReader::open() {
    // Close the previous file if it is open
    cleanup();
    
    file = new std::ifstream(filename);
    if (!file->is_open()) {
        cleanup();
        throw std::runtime_error("Cannot open file: " + filename);
    }
}

void FileReader::close() {
    cleanup();
}

bool FileReader::hasNext() const {
    return file != nullptr && file->is_open() && !file->eof();
}

std::string FileReader::next() {
    checkFileIsOpen();
    
    std::string line;
    if (std::getline(*file, line)) {
        return line;
    }
    return "";
}

void FileReader::reset() {
    checkFileIsOpen();
    
    file->clear();          // Resetting error flags
    file->seekg(0);         // Move to the beginning of the file
}

// Move constructor
FileReader::FileReader(FileReader&& other) noexcept 
    : filename(std::move(other.filename)), file(other.file) {
    other.file = nullptr;
}

// Move assignment operator
FileReader& FileReader::operator=(FileReader&& other) noexcept {
    if (this != &other) {
        cleanup();
        filename = std::move(other.filename);
        file = other.file;
        other.file = nullptr;
    }
    return *this;
}