#include <iostream>
#include <sstream>
#include <complex>
#include <cmath>
#include <regex>
void parse_equation(const std::string& equation, double& a, double& b, double& c) {
    std::regex re("([+-]?\\d*\\.?\\d*)x\\^2([+-]?\\d*\\.?\\d*)x([+-]?\\d*\\.?\\d*)=0");
    std::smatch match;
    std::string eq = equation;
    eq.erase(remove(eq.begin(), eq.end(), ' '), eq.end());

    if (std::regex_search(eq, match, re) && match.size() == 4) {
        a = match.str(1).empty() ? 1 : std::stod(match.str(1));
        b = match.str(2).empty() ? 0 : std::stod(match.str(2));
        c = match.str(3).empty() ? 0 : std::stod(match.str(3));
    } else {
        throw std::invalid_argument("Invalid quadratic equation format.");
    }
}
std::complex<double> to_euler_form(const std::complex<double>& z) {
    double r = std::abs(z);
    double theta = std::arg(z);
    return std::complex<double>(r, theta); // r*e^(i*theta)
}
void print_complex_root(const std::complex<double>& root) {
    std::cout << "\033[32m" << root.real() << "\033[0m";
    if (root.imag() != 0) {
        std::cout << (root.imag() > 0 ? " + " : " - ")
                  << "\033[34m" << std::abs(root.imag()) << "i\033[0m";
    }
}
void solve_quadratic(const std::string& equation) {
    double a, b, c;
    parse_equation(equation, a, b, c);
    std::complex<double> discriminant = std::pow(b, 2) - 4.0 * a * c;
    std::complex<double> root1 = (-b + std::sqrt(discriminant)) / (2.0 * a);
    std::complex<double> root2 = (-b - std::sqrt(discriminant)) / (2.0 * a);
    std::complex<double> root1_euler = to_euler_form(root1);
    std::complex<double> root2_euler = to_euler_form(root2);
    std::cout << "Roots:\n";
    std::cout << "Root 1: ";
    print_complex_root(root1);
    if (root1.imag() != 0) {
        std::cout << " (Euler form): " << root1_euler.real() << "*e^(i*" << root1_euler.imag() << ")";
    }
    std::cout << "\n";

    std::cout << "Root 2: ";
    print_complex_root(root2);
    if (root2.imag() != 0) {
        std::cout << " (Euler form): " << root2_euler.real() << "*e^(i*" << root2_euler.imag() << ")";
    }
    std::cout << "\n";
}
int main(int argc, char* argv[]) {
    if (argc != 2) {
        std::cerr << "Usage: " << argv[0] << " \"quadratic equation\"\n";
        return 1;
    }
    std::string equation = argv[1];
    try {
        solve_quadratic(equation);
    } catch (const std::exception& e) {
        std::cerr << e.what() << "\n";
        return 1;
    }
    return 0;
}
