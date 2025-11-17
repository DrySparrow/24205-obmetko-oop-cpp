#ifndef FILEREADER_H
#define FILEREADER_H

#include <string>
#include <fstream>

class FileReader {
private:
    std::string filename;
    std::ifstream* file;
    
    // Приватные методы для внутренней логики
    void checkFileIsOpen() const;
    void cleanup();

public:
    // Конструктор/деструктор
    FileReader(const std::string& filename);
    ~FileReader();
    
    // Основной публичный интерфейс
    void open();
    void close();
    bool hasNext() const;
    std::string next();
    void reset();
    
    // Запрет копирования (правило пяти)
    FileReader(const FileReader&) = delete;
    FileReader& operator=(const FileReader&) = delete;
    
    // Можно добавить move семантику
    FileReader(FileReader&& other) noexcept;
    FileReader& operator=(FileReader&& other) noexcept;
};

#endif