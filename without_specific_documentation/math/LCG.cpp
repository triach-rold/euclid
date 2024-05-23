#include <iostream>
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
int main() {
    int min = 1;
    int max = 6;
    for (int i = 0; i < 10; ++i) {
        std::cout << generateRandomNumberInRange(min, max) << std::endl;
    }
    return 0;
}
