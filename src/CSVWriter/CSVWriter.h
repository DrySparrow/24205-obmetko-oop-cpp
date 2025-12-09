#ifndef CSVWRITER_H
#define CSVWRITER_H

#include <string>
#include <fstream>
#include <vector>
#include <tuple>

class CSVWriter {
private:
    std::string filename;
    std::ofstream file;

public:
    void open();
    void close();
    CSVWriter(const std::string& filename);
    void write(const std::string& value1, int value2, double value3);
};

#endif