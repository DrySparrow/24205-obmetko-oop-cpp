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

void CSVWriter::write(const std::vector<std::string> args) {
    if (args.empty()) {
        file << "\n";
        return;
    }
    file << args[0];
    for (int i = 1; i < args.size(); ++i) {
        file << "," << args[i];
    }
    file << "\n";
}
