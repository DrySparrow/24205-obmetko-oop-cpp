#include "FileReader.h"
#include <stdexcept>

// Приватные методы
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

// Конструктор
FileReader::FileReader(const std::string& filename) 
    : filename(filename), file(nullptr) {}

// Деструктор
FileReader::~FileReader() {
    cleanup();
}

// Основной публичный интерфейс
void FileReader::open() {
    // Закрываем предыдущий файл если открыт
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
    
    file->clear();          // Сбрасываем флаги ошибок
    file->seekg(0);         // Перемещаемся в начало файла
}

// Move конструктор
FileReader::FileReader(FileReader&& other) noexcept 
    : filename(std::move(other.filename)), file(other.file) {
    other.file = nullptr;
}

// Move оператор присваивания
FileReader& FileReader::operator=(FileReader&& other) noexcept {
    if (this != &other) {
        cleanup();
        filename = std::move(other.filename);
        file = other.file;
        other.file = nullptr;
    }
    return *this;
}