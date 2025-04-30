#include <iostream>
#include <string>
#include <sstream>
#include <cctype>
#include <stack>
#include <cmath>
#include <map>

// Function to evaluate simple arithmetic expressions with constants
double eval_expression(double operand1, char op, double operand2) {
    switch (op) {
        case '+': return operand1 + operand2;
        case '-': return operand1 - operand2;
        case '*': return operand1 * operand2;
        case '/': return operand1 / operand2;
        default: return 0.0;
    }
}

// Function to perform constant folding on an arithmetic expression
std::string constant_folding(const std::string &expression) {
    std::stringstream exprStream(expression);
    std::stack<std::string> operators;  // Stack to hold operators
    std::stack<double> operands;        // Stack to hold operands (constants)
    std::string token;

    while (exprStream >> token) {
        if (isdigit(token[0])) {  // If the token is a number
            operands.push(std::stod(token));  // Push number onto the stack
        } else if (token == "+" || token == "-" || token == "*" || token == "/") {
            // If the token is an operator, push it onto the stack
            operators.push(token);
        } else {
            // Invalid token (can be handled as needed)
            std::cerr << "Invalid token: " << token << std::endl;
            return "";
        }

        // If there are two operands and an operator, perform constant folding
        if (operands.size() > 1 && !operators.empty()) {
            double operand2 = operands.top(); operands.pop();
            double operand1 = operands.top(); operands.pop();
            char op = operators.top()[0]; operators.pop();

            double result = eval_expression(operand1, op, operand2);
            operands.push(result);
        }
    }

    // If there's any remaining value, return the optimized expression
    if (operands.size() == 1) {
        std::stringstream result;
        result << operands.top();
        return result.str();
    } else {
        std::cerr << "Invalid expression!" << std::endl;
        return "";
    }
}

int main() {
    // Input arithmetic expression from the user
    std::string expression;
    std::cout << "Enter an arithmetic expression: ";
    std::getline(std::cin, expression);

    // Apply constant folding
    std::string optimized_expression = constant_folding(expression);

    // Output the optimized expression
    if (!optimized_expression.empty()) {
        std::cout << "Optimized Expression: " << optimized_expression << std::endl;
    }

    return 0;
}
