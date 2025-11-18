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

void CSVWriter::writerow(const std::tuple<std::string, int, double>& row) {
    file << std::get<0>(row) << "," << std::get<1>(row) << ","
            << std::fixed << std::setprecision(2) << std::get<2>(row) << "\n";
}