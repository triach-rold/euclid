#include <iostream>
#include <fstream>
#include <cstdlib>
#include <cstring>
const unsigned int a = 1103515245;
const unsigned int c = 12345;
const unsigned int m = 2147483648;
unsigned int seed = 2;
unsigned int generateRandomNumber() {
    seed = (a * seed + c) % m;
    return seed;
}
int generateRandomNumberInRange(int min, int max) {
    unsigned int randomNumber = generateRandomNumber();
    double normalized = static_cast<double>(randomNumber) / static_cast<double>(m);
    return static_cast<int>(normalized * (max - min) + min);
}
void appendToHistory(unsigned int number) {
    std::ofstream historyFile("resources/LCG_history.txt", std::ios::app);
    if (historyFile) {
        historyFile << number << std::endl;
    } else {
        std::cerr << "Error: Unable to open LCG_history.txt for writing.\n";
    }
}
unsigned int getLastSeedFromHistory() {
    std::ifstream historyFile("resources/LCG_history.txt");
    unsigned int lastSeed = seed; 
    if (historyFile) {
        std::string line;
        while (std::getline(historyFile, line)) {
            if (!line.empty()) {
                lastSeed = std::stoul(line);
            }
        }
    }
    return lastSeed;
}
int main(int argc, char* argv[]) {
    int min = 1;
    int max = 6;
    bool inRange = false;
    bool seedProvided = false;
    for (int i = 1; i < argc; ++i) {
        if (strcmp(argv[i], "--in-range") == 0) {
            if (i + 2 < argc) {
                min = std::atoi(argv[i + 1]);
                max = std::atoi(argv[i + 2]);
                inRange = true;
                i += 2;
            } else {
                std::cerr << "Error: --in-range flag requires two arguments (min and max).\n";
                return 1;
            }
        } else if (strcmp(argv[i], "--seed") == 0) {
            if (i + 1 < argc) {
                seed = std::atoi(argv[i + 1]);
                seedProvided = true;
                i += 1;
            } else {
                std::cerr << "Error: --seed flag requires one argument (seed value).\n";
                return 1;
            }
        }
    }
    if (!seedProvided) {
        seed = getLastSeedFromHistory();
    }
    for (int i = 0; i < 10; ++i) {
        unsigned int randomNumber;
        if (inRange) {
            randomNumber = generateRandomNumberInRange(min, max);
        } else {
            randomNumber = generateRandomNumber();
        }
        std::cout << randomNumber << std::endl;
        appendToHistory(randomNumber);
    }

    return 0;
}
