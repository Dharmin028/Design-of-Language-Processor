#include <iostream>
#include <string>
using namespace std;

string input; // The input string to be validated
int index = 0; // Current index for parsing

// Function declarations for the recursive descent parser
bool S();
bool L();
bool L_prime();

// Function to check if the current character matches the expected one
bool match(char expected) {
    if (index < input.length() && input[index] == expected) {
        index++;
        return true;
    }
    return false;
}

// Parse S → ( L ) | a
bool S() {
    if (match('(')) {
        if (L()) {
            if (match(')')) {
                return true;
            }
        }
    } else if (match('a')) {
        return true;
    }
    return false;
}

// Parse L → S L'
bool L() {
    if (S()) {
        if (L_prime()) {
            return true;
        }
    }
    return false;
}

// Parse L' → , S L' | ε (empty string)
bool L_prime() {
    if (match(',')) {
        if (S()) {
            if (L_prime()) {
                return true;
            }
        }
    }
    // ε (empty string) is allowed, so just return true
    return true;
}

// Main function to validate the input string
bool validateInput(string str) {
    input = str;
    index = 0;
    return S() && index == input.length(); // Ensure entire string is consumed
}

int main() {
    string str;
    cout << "Enter a string to validate: ";
    getline(cin, str);

    if (validateInput(str)) {
        cout << "Valid string" << endl;
    } else {
        cout << "Invalid string" << endl;
    }

    return 0;
}
