#ifndef FILEREADER_H
#define FILEREADER_H

#include <string>
#include <fstream>

class FileReader {
private:
    std::string filename;
    std::ifstream* file;
    
    void checkFileIsOpen() const;
    void cleanup();

public:
    FileReader(const std::string& filename);
    ~FileReader();
    
    void open();
    void close();
    bool hasNext() const;
    std::string next();
    void reset();
    
    FileReader(const FileReader&) = delete;
    FileReader& operator=(const FileReader&) = delete;
    
    FileReader(FileReader&& other) noexcept;
    FileReader& operator=(FileReader&& other) noexcept;
};

#endif