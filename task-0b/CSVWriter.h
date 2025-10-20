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
    CSVWriter(const std::string& filename);
    void open();
    void close();
    void write(const std::vector<std::tuple<std::string, int, double>>& data);
};

#endif