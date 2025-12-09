#ifndef CSVWRITER_H
#define CSVWRITER_H

#include <string>
#include <fstream>
#include <vector>
#include <tuple>
#include <iomanip>

class CSVWriter {
private:
    std::string filename;
    std::ofstream file;

public:
    CSVWriter(const std::string& filename);
    void open();
    void close();
    void write(const std::vector<std::string> args);
    
    static std::string formatFloat(double value, int precision = 2) {
        std::ostringstream oss;
        oss << std::fixed << std::setprecision(precision) << value;
        return oss.str();
    }
};

#endif