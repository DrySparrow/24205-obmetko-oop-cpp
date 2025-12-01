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
        WordCounter counter;
        
        reader.open();
        while (reader.hasNext()) {
            counter.handle(reader.next());
        }
        reader.close();

        WordStatistics stats(counter.getWordCount());
        auto vectorStatistics = stats.getStatistics();

        CSVWriter writer(argv[2]);
        writer.open();
        for (const auto& [word, count, percentage] : vectorStatistics) {
            writer.write(word, count, percentage);
        }
        writer.close();

        std::cout << "Successfully processed " << vectorStatistics.size() << " words to " << argv[2] << std::endl;
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