#include <iostream>
#include <cassert>
#include <cmath>
#define RED_TEXT "\033[1;31m"
#define GREEN_TEXT "\033[1;32m"
#define YELLOW_TEXT "\033[1;33m"
#define RESET_TEXT "\033[0m"
#define CYAN_TEXT "\033[1;36m"
double sterling_factorial(int n) {
    if (n < 0) {
        std::cerr << RED_TEXT "Error: Factorial of a negative number is undefined."  RESET_TEXT<< std::endl;
        return NAN;
    }
    if (n == 0) {
        return 1;
    }
    return sqrt(2 * M_PI * n) * pow(n / M_E, n);
}
unsigned long long factorial(int n) {
    if (n < 0) {
        std::cerr << RED_TEXT  "Error: Factorial of a negative number is undefined." RESET_TEXT<< std::endl;
        return 0;
    }
    unsigned long long result = 1;
    for (int i = 2; i <= n; ++i) {
        result *= i;
    }
    return result;
}
int main() {
    for (int n = -1; n <= 30; ++n) {
        std::cout << "n = " << n << std::endl;
        std::cout <<  YELLOW_TEXT "Sterling's Approximation: " << sterling_factorial(n) << RESET_TEXT << std::endl;
        std::cout <<  GREEN_TEXT "Factorial: " << factorial(n) << RESET_TEXT << std::endl;
        std::cout <<  CYAN_TEXT ((factorial(n) - sterling_factorial(n)) / static_cast<double>(factorial(n))) * 100 << RESET_TEXT << std:endl;
        std::cout << std::endl;
    }
    return 0;
}
