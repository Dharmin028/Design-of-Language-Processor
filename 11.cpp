#include <iostream>
#include <stack>
#include <string>
#include <sstream>
#include <map>

using namespace std;

struct Quadruple {
    string op;   // Operator
    string arg1; // Operand 1
    string arg2; // Operand 2
    string result; // Result
};

map<int, Quadruple> quadruples; // To store the quadruples
int tempCount = 1; // Temporary variable counter

// Function to create a new temporary variable
string newTemp() {
    stringstream ss;
    ss << "t" << tempCount++;
    return ss.str();
}

// Function to generate the quadruples from the expression
void generateQuadruples(const string& expression) {
    stack<string> operators;
    stack<string> operands;
    
    for (int i = 0; i < expression.length(); i++) {
        if (isdigit(expression[i])) { 
            // If it's a number, push it to the operand stack
            operands.push(string(1, expression[i]));
        }
        else if (expression[i] == '+' || expression[i] == '-') {
            // Handle + and - operators
            while (!operators.empty() && (operators.top() == "*" || operators.top() == "/")) {
                string op = operators.top();
                operators.pop();
                string operand2 = operands.top();
                operands.pop();
                string operand1 = operands.top();
                operands.pop();
                string temp = newTemp();
                quadruples[tempCount - 1] = {op, operand1, operand2, temp};
                operands.push(temp);
            }
            operators.push(string(1, expression[i]));
        }
        else if (expression[i] == '*' || expression[i] == '/') {
            // Handle * and / operators
            operators.push(string(1, expression[i]));
        }
        else if (expression[i] == '(') {
            // Push '(' to operators stack
            operators.push(string(1, expression[i]));
        }
        else if (expression[i] == ')') {
            // Pop from the operator stack until '(' is encountered
            while (operators.top() != "(") {
                string op = operators.top();
                operators.pop();
                string operand2 = operands.top();
                operands.pop();
                string operand1 = operands.top();
                operands.pop();
                string temp = newTemp();
                quadruples[tempCount - 1] = {op, operand1, operand2, temp};
                operands.push(temp);
            }
            operators.pop(); // pop '('
        }
    }
    
    // Process remaining operators in the stack
    while (!operators.empty()) {
        string op = operators.top();
        operators.pop();
        string operand2 = operands.top();
        operands.pop();
        string operand1 = operands.top();
        operands.pop();
        string temp = newTemp();
        quadruples[tempCount - 1] = {op, operand1, operand2, temp};
        operands.push(temp);
    }
}

// Function to print the quadruple table
void printQuadruples() {
    cout << "Operator\tOperand 1\tOperand 2\tResult\n";
    for (const auto& q : quadruples) {
        cout << q.second.op << "\t" << q.second.arg1 << "\t" 
             << q.second.arg2 << "\t" << q.second.result << endl;
    }
}

int main() {
    string expression;
    cout << "Enter an arithmetic expression: ";
    getline(cin, expression);
    
    generateQuadruples(expression);
    printQuadruples();
    
    return 0;
}
