#include <iostream>
#include <cstdlib>
#include <cstring>
const unsigned int a = 1103515245;
const unsigned int c = 12345;
const unsigned int m = 2147483648;
unsigned int seed = 1;
unsigned int generateRandomNumber() {
    seed = (a * seed + c) % m;
    return seed;
}
int generateRandomNumberInRange(int min, int max) {
    unsigned int randomNumber = generateRandomNumber();
    double normalized = static_cast<double>(randomNumber) / static_cast<double>(m);
    return static_cast<int>(normalized * (max - min) + min);
}
int main(int argc, char* argv[]) {
    int min = 1;
    int max = 6;
    bool inRange = false;
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
        }
    }
    for (int i = 0; i < 10; ++i) {
        if (inRange) {
            std::cout << generateRandomNumberInRange(min, max) << std::endl;
        } else {
            std::cout << generateRandomNumber() << std::endl;
        }
    }
    return 0;
}
