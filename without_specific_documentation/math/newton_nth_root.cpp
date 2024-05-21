#include <iostream>
#include <cmath>
#include <chrono>
#include <cassert>
using namespace std;
using namespace std::chrono;
double newton_nth_root(int a, int n) {
    double x = a / 2.0; // Initial guess
    double epsilon = 1e-6; // Tolerance
    while(abs(pow(x, n) - a) > epsilon){
        x = x - (pow(x, n) - a) / (n * pow(x, n - 1)); // Newton-Raphson iteration
    }
    return x;
}
int main() {
    // Test cases using cassert
    assert(abs(newton_nth_root(1, 1) - 1) < 1e-6); // nth root of 1 should be 1 for any n
    assert(abs(newton_nth_root(0, 5) - 0) < 1e-6); // nth root of 0 should be 0 for any n
    assert(abs(newton_nth_root(16, 4) - 2) < 1e-6); // 4th root of 16 is 2
    assert(abs(newton_nth_root(27, 3) - 3) < 1e-6); // Cube root of 27 is 3
    assert(abs(newton_nth_root(81, 4) - 3) < 1e-6); // 4th root of 81 is 3
    cout << "All test cases passed!" << endl; 
    return 0;
}
