# Numerical Integral Evaluator

C++ code to solve integrals via the basic definition of a definite integral.

## Mathematical Prerequisites
1. The function must be **continuous** and **bounded** between the limits specified.
2. The function must have defined values for the upper and lower limits.

## How does it work?
1. This code uses the literal definition of a definite integral.
2. Since the function is defined as *continuous* between the two intervals, it can be visualized as the area under the curve, over the x-axis.
3. Since the value of the definite integral is the area under the curve, we can find the definite integral if we find the area enclosed by the curve.
4. This area under the curve can be visualized as the sum of the areas of infinite rectangles. These rectangles, or "strips" are infinitesimally small. This is mathematically known as a [Riemann Sum](https://en.wikipedia.org/wiki/Riemann_sum).

## How to run it?
1. The file is in C++. It requires you to have the GNU C++ compiler (doesn't need to be GNU, but it's tested on GNU) so that it can be turned into an executable for your computer to run.
2. Assuming you already have GNU, open up your terminal of choice and put in the command `g++ integral.cpp` in the directory where you've saved the file. (You can use the `cd` command to navigate through your directories.)
3. Assuming the last step went smoothly and without errors (which it should), you need to type in `./a.out (function) (upper_bound) (lower_bound) --increment (increment_steps_value) --simpson --trapezoid`. And it should calculate. Note that the increment flag is optional and it is set to 1,000,000 by default. Bigger numbers make the result more accurate, but evaluation time will also increase. The simpson flag is also optional (specify it to evaluate by simpson's rule, but this is disabled by default). The trapezoid flag is also optional (specify it to evaluate by the trapezoidal rule- but this is also disabled by default). Please note that you can only use one mode at a time.

## Supported Functions?

* sin(x)
* cos(x)
* tan(x)
* cosec(x)
* sec(x)
* cot(x)
* asin(x)
* acos(x)
* atan(x)
* sinh(x)
* cosh(x)
* tanh(x)
* asinh(x)
* acosh(x)
* atanh(x)
* log(x)
* ln(x)
* log(base)(x)
* gamma(x)
* lgamma(x)
* exp(x)
* sqrt(x)
* exp2(x)
* exp10(x)
* cbrt(x)
* abs(x)
* sgn(x)
