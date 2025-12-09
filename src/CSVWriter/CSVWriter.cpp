#include "CSVWriter.h"
#include <stdexcept>
#include <iomanip>

CSVWriter::CSVWriter(const std::string& filename) : filename(filename) {}

void CSVWriter::open() {
    file.open(filename);
    if (!file.is_open()) {
        throw std::runtime_error("Cannot open file: " + filename);
    }
}

void CSVWriter::close() {
    if (file.is_open()) {
        file.close();
    }
}

void CSVWriter::write(const std::string& value1, int value2, double value3) {
    file << value1 << "," << value2 << "," << std::fixed << std::setprecision(2) << value3 << "\n";
}