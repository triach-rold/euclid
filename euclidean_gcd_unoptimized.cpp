#include<iostream>
#include<stdio.h>
#include<cmath>
#include <cassert>
using namespace std;
int gcd(int a, int b){
  if(a<0||b<0){
    return 0;
  }
  if(b>a){
    a = a + b;
    b = a - b;
    a = a - b;
  }
  int r_0 = 10;
  int q_0 = 10;
  while(r_0!=0){
    q_0 = floor(a/b);
    r_0 = a - (q_0*b);
    a = b;
    b = r_0;
  }
  return a;
}
int main() {
    // Test cases
    assert(gcd(12, 18) == 6); // GCD of 12 and 18 is 6
    assert(gcd(1071, 462) == 21); // GCD of 1071 and 462 is 21
    assert(gcd(15, 0) == 15); // GCD of 15 and 0 is 15
    assert(gcd(-10, 5) == 0); // Negative input returns 0
    assert(gcd(0, 0) == 0); // GCD of 0 and 0 is 0
    assert(gcd(123456, 7890) == 6); // GCD of large numbers

    std::cout << "All test cases passed!\n";
    return 0;
}
