#include <iostream>
#include <cassert>
#include <cmath>
double sterling_factorial(int n) {
    if (n < 0) {
        std::cerr << "Error: Factorial of a negative number is undefined." << std::endl;
        return NAN;
    }
    if (n == 0) {
        return 1;
    }
    return sqrt(2 * M_PI * n) * pow(n / M_E, n);
}
unsigned long long factorial(int n) {
    if (n < 0) {
        std::cerr << "Error: Factorial of a negative number is undefined." << std::endl;
        return 0;
    }
    unsigned long long result = 1;
    for (int i = 2; i <= n; ++i) {
        result *= i;
    }
    return result;
}
int main() {
    for (int n = 0; n <= 30; ++n) {
        std::cout << "n = " << n << std::endl;
        std::cout << "Sterling's Approximation: " << sterling_factorial(n) << std::endl;
        std::cout << "Factorial: " << factorial(n) << std::endl;
        std::cout << ((factorial(n) - sterling_factorial(n)) / static_cast<double>(factorial(n))) * 100;
        std::cout << std::endl;
    }
    return 0;
}
