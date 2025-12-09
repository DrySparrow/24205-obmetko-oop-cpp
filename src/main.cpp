#include "game.h"
#include <iostream>
#include <string>
#include <cstring>

void printUsage(const char* programName) {
    std::cout << "Usage: " << programName << " [options] [input_file]" << std::endl;
    std::cout << "Options:" << std::endl;
    std::cout << "  -i <n>, --iterations=<n>  Number of iterations (offline mode)" << std::endl;
    std::cout << "  -o <file>, --output=<file> Output file (offline mode)" << std::endl;
    std::cout << "  -t <n>, --tick=<n>        Tick mode with n iterations" << std::endl;
    std::cout << "  --help                    Show this help message" << std::endl;
    std::cout << std::endl;
    std::cout << "Modes:" << std::endl;
    std::cout << "  1. Interactive mode: " << programName << " [input_file]" << std::endl;
    std::cout << "  2. Tick mode: " << programName << " [input_file] -t <n>" << std::endl;
    std::cout << "  3. Offline mode: " << programName << " <input_file> -i <n> -o <output_file>" << std::endl;
}

int main(int argc, char* argv[]) {
    Game game;
    std::string inputFile;
    std::string outputFile;
    int iterations = 0;
    int tickIterations = 0;
    bool offlineMode = false;
    bool tickMode = false;
    
    for (int i = 1; i < argc; ++i) {
        std::string arg = argv[i];
        
        if (arg == "--help") {
            printUsage(argv[0]);
            return 0;
        }
        else if (arg == "-i" && i + 1 < argc) {
            iterations = std::stoi(argv[++i]);
            offlineMode = true;
        }
        else if (arg.rfind("--iterations=", 0) == 0) {
            iterations = std::stoi(arg.substr(13));
            offlineMode = true;
        }
        else if (arg == "-o" && i + 1 < argc) {
            outputFile = argv[++i];
            offlineMode = true;
        }
        else if (arg.rfind("--output=", 0) == 0) {
            outputFile = arg.substr(9);
            offlineMode = true;
        }
        else if (arg == "-t" && i + 1 < argc) {
            tickIterations = std::stoi(argv[++i]);
            tickMode = true;
        }
        else if (arg.rfind("--tick=", 0) == 0) {
            tickIterations = std::stoi(arg.substr(7));
            tickMode = true;
        }
        else if (arg[0] != '-') {
            inputFile = arg;
        }
    }
    
    // Validate arguments
    if (offlineMode && tickMode) {
        std::cerr << "Error: Cannot use both offline and tick modes simultaneously!" << std::endl;
        printUsage(argv[0]);
        return 1;
    }
    
    // Load universe if input file is provided
    if (!inputFile.empty() && !offlineMode) {
        std::cout << "Note: File loading in interactive/tick mode to be implemented" << std::endl;
    }
    
    // Run appropriate mode
    if (offlineMode) {
        if (inputFile.empty() || outputFile.empty() || iterations <= 0) {
            std::cerr << "Error: Offline mode requires input file, output file, and positive iterations!" << std::endl;
            printUsage(argv[0]);
            return 1;
        }
        game.runOfflineMode(inputFile, iterations, outputFile);
    }
    else if (tickMode) {
        game.runTickMode(tickIterations);
    }
    else {
        game.runInteractive();
    }
    
    return 0;
}