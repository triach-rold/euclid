#include <iostream>
#include <cmath>
#include <chrono>
#include <cassert>
using namespace std;
using namespace std::chrono;
double newton_sqrt(int a) {
    double x = a / 2.0; // Initial guess
    double epsilon = 1e-6; // Tolerance
    while(abs(x * x - a) > epsilon){
        x = (x + a / x) / 2.0; // Newton-Raphson iteration
    }
    return x;
}
int main() {
    // Test cases using cassert
    assert(abs(newton_sqrt(0) - sqrt(0)) < 1e-6); // Square root of 0
    assert(abs(newton_sqrt(1) - sqrt(1)) < 1e-6); // Square root of 1
    assert(abs(newton_sqrt(4) - sqrt(4)) < 1e-6); // Square root of a perfect square
    assert(abs(newton_sqrt(25) - sqrt(25)) < 1e-6); // Square root of a perfect square
    assert(abs(newton_sqrt(2) - sqrt(2)) < 1e-6); // Square root of a non-perfect square

    cout << "All test cases passed!" << endl;
    
    return 0;
}
