#include <iostream>
#include <fstream>
#include <regex>
#include <set>
#include <map>
using namespace std;

// Define keyword list
set<string> keywords = {
    "int", "float", "char", "double", "if", "else", "while", "for", "return", "void", "struct"
};

set<char> operators = {'+', '-', '*', '/', '=', '<', '>', '&', '|'};
set<char> punctuations = {';', ',', '(', ')', '{', '}'};

map<string, int> symbolTable;

bool isKeyword(const string &word) {
    return keywords.find(word) != keywords.end();
}

bool isIdentifier(const string &word) {
    return regex_match(word, regex("[a-zA-Z_][a-zA-Z0-9_]*"));
}

bool isConstant(const string &word) {
    return regex_match(word, regex("[0-9]+(\\.[0-9]+)?"));
}

bool isString(const string &word) {
    return regex_match(word, regex("'.'|\".*\""));
}

void tokenize(const string &line, int &lineNum) {
    string token;
    for (size_t i = 0; i < line.length(); ++i) {
        char ch = line[i];

        // Skip whitespaces
        if (isspace(ch)) {
            continue;
        }

        // Skip single-line comments
        if (ch == '/' && i + 1 < line.size() && line[i + 1] == '/') {
            break;
        }

        // Handle multi-line comments
        if (ch == '/' && i + 1 < line.size() && line[i + 1] == '*') {
            i += 2;
            while (i + 1 < line.length() && !(line[i] == '*' && line[i + 1] == '/')) {
                i++;
            }
            i++; // skip final '/'
            continue;
        }

        // Handle strings and characters
        if (ch == '"' || ch == '\'') {
            char quote = ch;
            token += ch;
            i++;
            while (i < line.length() && line[i] != quote) {
                token += line[i++];
            }
            token += quote;
            cout << "String: " << token << endl;
            token.clear();
            continue;
        }

        // Handle punctuations
        if (punctuations.count(ch)) {
            cout << "Punctuation: " << ch << endl;
            continue;
        }

        // Handle operators
        if (operators.count(ch)) {
            cout << "Operator: " << ch << endl;
            continue;
        }

        // Handle words and numbers
        if (isalnum(ch) || ch == '_') {
            token.clear();
            while (i < line.length() && (isalnum(line[i]) || line[i] == '_')) {
                token += line[i++];
            }
            i--; // step back
            if (isKeyword(token))
                cout << "Keyword: " << token << endl;
            else if (isConstant(token))
                cout << "Constant: " << token << endl;
            else if (isIdentifier(token)) {
                cout << "Identifier: " << token << endl;
                symbolTable[token]++;
            } else
                cout << "Lexical Error: " << token << " at line " << lineNum << endl;
        }
    }
}

int main() {
    ifstream infile("input.c"); // Your C file
    string line;
    int lineNum = 1;

    if (!infile.is_open()) {
        cerr << "Error opening file." << endl;
        return 1;
    }

    cout << "TOKENS\n";
    while (getline(infile, line)) {
        tokenize(line, lineNum);
        lineNum++;
    }

    // Symbol Table Output
    cout << "\nSYMBOL TABLE ENTRIES:\n";
    int idx = 1;
    for (auto &entry : symbolTable) {
        cout << idx++ << ") " << entry.first << endl;
    }

    infile.close();
    return 0;
}
