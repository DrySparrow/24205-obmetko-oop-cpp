#include <iostream>
#include <exception>
#include "FileReader.h"
#include "WordCounter.h"
#include "WordStatistics.h"
#include "CSVWriter.h"

int main(int argc, char* argv[]) {
    if (argc != 3) {
        std::cerr << "Usage: " << argv[0] << " <input.txt> <output.csv>" << std::endl;
        std::cout << "Press Enter to exit...";
        std::cin.get();
        return 1;
    }

    try {
        FileReader reader(argv[1]);
        WordCounter counter(reader);
        counter.countWords();

        WordStatistics stats(counter.getWordCount());
        auto statistics = stats.getStatistics();

        CSVWriter writer(argv[2]);
        writer.open();
        writer.write(statistics);
        writer.close();

        std::cout << "Successfully processed " << statistics.size() << " words to " << argv[2] << std::endl;
        std::cout << "Press Enter to exit...";
        std::cin.get();

    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
        std::cout << "Press Enter to exit...";
        std::cin.get();
        return 1;
    }

    return 0;
}