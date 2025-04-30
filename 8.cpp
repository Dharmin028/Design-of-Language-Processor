#include <iostream>
#include <map>
#include <set>
#include <vector>
#include <string>
#include <iterator>
using namespace std;

map<string, vector<string>> productions;
map<string, set<char>> first, follow;
map<string, map<char, string>> parsingTable;

// Function to compute the First set for a non-terminal
void computeFirst(string nonTerminal) {
    // If already computed, return
    if (!first[nonTerminal].empty()) return;

    for (const string& production : productions[nonTerminal]) {
        if (production == "ε") {
            first[nonTerminal].insert('ε');
        } else {
            for (char symbol : production) {
                if (isupper(symbol)) {
                    computeFirst(string(1, symbol));
                    first[nonTerminal].insert(first[string(1, symbol)].begin(), first[string(1, symbol)].end());
                    if (first[string(1, symbol)].count('ε') == 0) break;
                } else {
                    first[nonTerminal].insert(symbol);
                    break;
                }
            }
        }
    }
}

// Function to compute the Follow set for a non-terminal
void computeFollow(string nonTerminal) {
    if (!follow[nonTerminal].empty()) return;

    if (nonTerminal == "S") follow[nonTerminal].insert('$');

    for (auto& prod : productions) {
        for (const string& production : prod.second) {
            for (int i = 0; i < production.size(); i++) {
                if (production[i] == nonTerminal) {
                    if (i + 1 < production.size() && !isupper(production[i + 1])) {
                        follow[nonTerminal].insert(production[i + 1]);
                    }
                    if (i + 1 < production.size() && isupper(production[i + 1])) {
                        computeFirst(string(1, production[i + 1]));
                        follow[nonTerminal].insert(first[string(1, production[i + 1])].begin(), first[string(1, production[i + 1])].end());
                        if (first[string(1, production[i + 1])].count('ε') > 0 && i + 1 == production.size()) {
                            computeFollow(string(1, prod.first[0]));
                            follow[nonTerminal].insert(follow[string(1, prod.first[0])].begin(), follow[string(1, prod.first[0])].end());
                        }
                    }
                    if (i + 1 == production.size()) {
                        computeFollow(string(1, prod.first[0]));
                        follow[nonTerminal].insert(follow[string(1, prod.first[0])].begin(), follow[string(1, prod.first[0])].end());
                    }
                }
            }
        }
    }
}

// Function to construct the predictive parsing table
void constructParsingTable() {
    for (auto& prod : productions) {
        for (const string& production : prod.second) {
            set<char> firstSet;
            if (production == "ε") {
                firstSet.insert('ε');
            } else {
                for (char symbol : production) {
                    if (isupper(symbol)) {
                        computeFirst(string(1, symbol));
                        firstSet.insert(first[string(1, symbol)].begin(), first[string(1, symbol)].end());
                        if (first[string(1, symbol)].count('ε') == 0) break;
                    } else {
                        firstSet.insert(symbol);
                        break;
                    }
                }
            }

            for (char terminal : firstSet) {
                if (terminal != 'ε') {
                    parsingTable[prod.first][terminal] = production;
                } else {
                    if (follow[prod.first].empty()) {
                        computeFollow(prod.first);
                    }
                    for (char followSymbol : follow[prod.first]) {
                        parsingTable[prod.first][followSymbol] = production;
                    }
                }
            }
        }
    }
}

// Function to validate the input string against the grammar
bool validateString(const string& input) {
    string stack = "S$"; // Stack initialized with start symbol and end of input symbol
    string inputStr = input + "$"; // Add the end of input symbol

    int index = 0;
    while (!stack.empty() && index < inputStr.size()) {
        char top = stack.back();
        char currentChar = inputStr[index];

        if (isupper(top)) {
            if (parsingTable[string(1, top)].count(currentChar)) {
                string production = parsingTable[string(1, top)][currentChar];
                stack.pop_back();
                for (int i = production.size() - 1; i >= 0; i--) {
                    if (production[i] != 'ε') {
                        stack.push_back(production[i]);
                    }
                }
            } else {
                return false;
            }
        } else if (top == currentChar) {
            stack.pop_back();
            index++;
        } else {
            return false;
        }
    }

    return stack.empty() && index == inputStr.size();
}

// Function to print the parsing table
void printParsingTable() {
    for (const auto& row : parsingTable) {
        for (const auto& col : row.second) {
            cout << "M[" << row.first << "][" << col.first << "] = " << col.second << endl;
        }
    }
}

int main() {
    // Define the grammar (example grammar)
    productions["S"] = {"A B C", "D"};
    productions["A"] = {"a", "ε"};
    productions["B"] = {"b", "ε"};
    productions["C"] = {"( S )", "c"};
    productions["D"] = {"A C"};

    // Compute First and Follow sets
    for (const auto& prod : productions) {
        computeFirst(prod.first);
        computeFollow(prod.first);
    }

    // Construct the parsing table
    constructParsingTable();

    // Print the parsing table
    cout << "Predictive Parsing Table:" << endl;
    printParsingTable();

    // Check if the grammar is LL(1)
    bool isLL1 = true;
    for (const auto& row : parsingTable) {
        for (const auto& col : row.second) {
            if (parsingTable[row.first].count(col.first) > 1) {
                isLL1 = false;
                break;
            }
        }
        if (!isLL1) break;
    }

    if (isLL1) {
        cout << "The grammar is LL(1)." << endl;

        // Input string to validate
        string input;
        cout << "Enter a string to validate: ";
        cin >> input;

        // Validate the string against the grammar
        if (validateString(input)) {
            cout << "Valid string." << endl;
        } else {
            cout << "Invalid string." << endl;
        }
    } else {
        cout << "The grammar is not LL(1)." << endl;
    }

    return 0;
}
