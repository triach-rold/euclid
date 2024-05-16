#include <iostream>
#include <cassert>
int gcd(int a, int b) {
    if (a < 0 || b < 0)
        return 0;
    if (b == 0)
        return std::abs(a);
    while (b != 0) {
        int temp = b;
        b = a % b;
        a = temp;
    }
    return std::abs(a);
}
int main() {
    // Test cases
    assert(gcd(12, 18) == 6);     // GCD of 12 and 18 is 6
    assert(gcd(1071, 462) == 21);  // GCD of 1071 and 462 is 21
    assert(gcd(15, 0) == 15);      // GCD of 15 and 0 is 15
    assert(gcd(-10, 5) == 0);      // Negative input returns 0
    assert(gcd(0, 0) == 0);        // GCD of 0 and 0 is 0
    assert(gcd(123456, 7890) == 6); // GCD of large numbers
    return 0;
}
