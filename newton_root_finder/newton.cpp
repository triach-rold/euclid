#include <iostream>
#include <sstream>
#include <string>
#include <cctype>
#include <cmath>
#include <stdexcept>
#include <map>
#define RED_TEXT "\033[1;31m"
#define GREEN_TEXT "\033[1;32m"
#define YELLOW_TEXT "\033[1;33m"
#define RESET_TEXT "\033[0m"
class Parser {
public:
    Parser(const std::string& expression) : expr(expression), pos(0) {}
    double parse() {
        pos = 0;
        return parseExpression();
    }
private:
    std::string expr;
    size_t pos;
    double parseExpression() {
        double result = parseTerm();
        while (pos < expr.size()) {
            if (expr[pos] == '+') {
                pos++;
                result += parseTerm();
            } else if (expr[pos] == '-') {
                pos++;
                result -= parseTerm();
            } else {
                break;
            }
        }
        return result;
    }
    double parseTerm() {
        double result = parseFactor();
        while (pos < expr.size()) {
            if (expr[pos] == '*') {
                pos++;
                result *= parseFactor();
            } else if (expr[pos] == '/') {
                pos++;
                double divisor = parseFactor();
                if (divisor == 0) throw std::runtime_error(RED_TEXT "Division by zero" RESET_TEXT);
                result /= divisor;
            } else {
                break;
            }
        }
        return result;
    }
    double parseFactor() {
        double result = parsePrimary();
        while (pos < expr.size()) {
            if (expr[pos] == '^') {
                pos++;
                result = pow(result, parsePrimary());
            } else {
                break;
            }
        }
        return result;
    }
    double parsePrimary() {
        if (expr[pos] == '(') {
            pos++;
            double result = parseExpression();
            if (pos < expr.size() && expr[pos] == ')') {
                pos++;
            } else {
                throw std::runtime_error(RED_TEXT "Mismatched parentheses" RESET_TEXT);
            }
            return result;
        } else if (isalpha(expr[pos])) {
            return parseFunction();
        } else {
            return parseNumber();
        }
    }
    double parseNumber() {
        size_t startPos = pos;
        if (expr[pos] == '-') {
            pos++;
        }
        while (pos < expr.size() && (isdigit(expr[pos]) || expr[pos] == '.')) {
            pos++;
        }
        return std::stod(expr.substr(startPos, pos - startPos));
    }
    double parseFunction() {
        std::string func;
        while (pos < expr.size() && isalpha(expr[pos])) {
            func += expr[pos++];
        }
        if (func == "e") {
            return M_E;
        }
        if (pos < expr.size() && expr[pos] == '(') {
            pos++;
            if (func == "logb") {
                double base = parseExpression();
                if (pos < expr.size() && expr[pos] == ')') {
                    pos++;
                } else {
                    throw std::runtime_error(RED_TEXT "Mismatched parentheses after logb base" RESET_TEXT);
                }
                if (pos < expr.size() && expr[pos] == '(') {
                    pos++;
                    double arg = parseExpression();
                    if (pos < expr.size() && expr[pos] == ')') {
                        pos++;
                        return log(arg) / log(base);
                    } else {
                        throw std::runtime_error(RED_TEXT "Mismatched parentheses after logb argument" RESET_TEXT);
                    }
                } else {
                    throw std::runtime_error(RED_TEXT "Missing parentheses for logb argument" RESET_TEXT);
                }
            } else {
                double arg = parseExpression();
                if (pos < expr.size() && expr[pos] == ')') {
                    pos++;
                } else {
                    throw std::runtime_error(RED_TEXT "Mismatched parentheses" RESET_TEXT);
                }
                if (func == "sin") return sin(arg);
                if (func == "cos") return cos(arg);
                if (func == "tan") return tan(arg);
                if (func == "cosec") return 1.0 / sin(arg);
                if (func == "sec") return 1.0 / cos(arg);
                if (func == "cot") return 1.0 / tan(arg);
                if (func == "sqrt") return sqrt(arg);
                if (func == "abs") return fabs(arg);
                if (func == "exp") return exp(arg);
                if (func == "sgn") return (arg > 0) - (arg < 0);
                if (func == "log") return log(arg);
                if (func == "ln") return log(arg);
                if (func == "asin") return asin(arg);
                if (func == "acos") return acos(arg);
                if (func == "atan") return atan(arg);
                if (func == "sinh") return sinh(arg);
                if (func == "cosh") return cosh(arg);
                if (func == "tanh") return tanh(arg);
                if (func == "asinh") return asinh(arg);
                if (func == "acosh") return acosh(arg);
                if  (func == "atanh") return atanh(arg);
                if (func == "gamma") return tgamma(arg);
                if (func == "lgamma") return lgamma(arg);
                if (func == "exp2") return exp2(arg);
                if (func == "exp10") return pow(10, arg);
                if (func == "cbrt") return cbrt(arg);
                throw std::runtime_error(RED_TEXT "Unknown function: " + func + RESET_TEXT);
            }
        }
        throw std::runtime_error(RED_TEXT "Unexpected identifier: " + func + RESET_TEXT);
    }
};

double evaluate_function(const std::string& expression, double x) {
    std::string replacedExpression;
    for (size_t i = 0; i < expression.size(); ++i) {
            if (expression[i] == 'x') {
            replacedExpression += std::to_string(x);
        }        else {
            replacedExpression += expression[i];
        }
    }
    Parser parser(replacedExpression);
    return parser.parse();
}

double derivative(const std::string& expression, double x, double h = 1e-5) {
    return (evaluate_function(expression, x + h) - evaluate_function(expression, x - h)) / (2 * h);
}

double newtons_method(const std::string& function, double initial_guess, double tolerance = 1e-4, int max_iterations = 1000) {
    double x = initial_guess;
    for (int i = 0; i < max_iterations; ++i) {
        double f = evaluate_function(function, x);
        double f_prime = derivative(function, x);
        if (fabs(f_prime) < 1e-12) {
            throw std::runtime_error(RED_TEXT "Derivative is too small, no convergence" RESET_TEXT);
        }

        double x_next = x - f / f_prime;

        if (fabs(x_next - x) < tolerance) {
            return x_next;
        }

        x = x_next;
    }
    double f = evaluate_function(function, x);
    if (fabs(f) < tolerance) {
        return x;
    }
    std::ostringstream oss;
    oss << RED_TEXT "Maximum iterations reached. Best guess is " << x << RESET_TEXT;
    throw std::runtime_error(oss.str());
}

int main(int argc, char* argv[]) {
    if (argc < 3 || argc > 7) {
        std::cerr << "Usage: " << argv[0] << " \"function\" initial_guess [--tolerance tolerance_value] [--max-iterations max_iterations]" << std::endl;
        return 1;
    }
    std::string function = argv[1];
    double initial_guess = std::stod(argv[2]);
    double tolerance = 1e-4;
    int max_iterations = 1000;

    for (int i = 3; i < argc; ++i) {
        std::string arg = argv[i];
        if (arg == "--tolerance" && i + 1 < argc) {
            tolerance = std::stod(argv[++i]);
        } else if (arg == "--max-iterations" && i + 1 < argc) {
            max_iterations = std::stoi(argv[++i]);
        } else {
            std::cerr << RED_TEXT "Invalid argument: " << arg << RESET_TEXT << std::endl;
            return 1;
        }
    }

    try {
        double root = newtons_method(function, initial_guess, tolerance, max_iterations);
        std::cout << GREEN_TEXT "Root found: " << root << RESET_TEXT << std::endl;
    } catch (const std::exception& e) {
        std::cerr << RED_TEXT "Error: " << e.what() << RESET_TEXT << std::endl;
        return 1;
    }

    return 0;
}