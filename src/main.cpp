#include <iostream>
#include <exception>
#include "FileReader.h"
#include "WordCounter.h"
#include "WordStatistics.h"
#include "CSVWriter.h"
#include "LineParser.h"

#pragma once

int main(int argc, char* argv[]) {
    if (argc != 3) {
        std::cerr << "Usage: " << argv[0] << " <input.txt> <output.csv>" << std::endl;
        return 1;
    }

    try {
        FileReader reader(argv[1]);
        WordCounter counter;
        
        reader.open();
        LineParser lp;
        std::vector<std::string> line;
        while (reader.hasNext()) {
            line = lp.parse(reader.next());
            counter.handle(line);
        }
        reader.close(); 

        WordStatistics stats(counter.getWordCount());
        auto vectorStatistics = stats.getStatistics();

        CSVWriter writer(argv[2]);
        writer.open();
        for (const auto& [word, count, percentage] : vectorStatistics) {
            writer.write({
                word,
                std::to_string(count),
                CSVWriter::formatFloat(percentage)
            });
        }
        writer.close();

        std::cout << "Successfully processed " << vectorStatistics.size() << " words to " << argv[2] << std::endl;

    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
        return 1;
    }

    return 0;
}