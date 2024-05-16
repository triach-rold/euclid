#include <iostream>
#include <cassert>
int nCr(int n, int r) {
    if (r > n) return 0;
    if (r == 0 || r == n) return 1;
    long long res = 1;
    for (int i = 0; i < r; ++i) {
        res *= (n - i);
        res /= (i + 1);
    }
    return static_cast<int>(res);
}
int main() {
    assert(nCr(5, 2) == 10);   // 5 choose 2 = 10
    assert(nCr(6, 3) == 20);   // 6 choose 3 = 20
    assert(nCr(10, 0) == 1);   // 10 choose 0 = 1
    assert(nCr(10, 10) == 1);  // 10 choose 10 = 1
    assert(nCr(10, 5) == 252); // 10 choose 5 = 252
    return 0;
}
