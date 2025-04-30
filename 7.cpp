#include <iostream>
#include <set>
#include <map>
#include <vector>
#include <string>
#include <iterator>
using namespace std;

map<char, set<char>> first, follow;
map<char, vector<string>> productions;

// Function to compute the First set for a non-terminal
void computeFirst(char nonTerminal) {
    // If already computed, return
    if (!first[nonTerminal].empty()) return;

    for (const string& production : productions[nonTerminal]) {
        // Handle each production for the non-terminal
        if (production == "ε") {
            first[nonTerminal].insert('ε');
        } else {
            for (char symbol : production) {
                if (isupper(symbol)) {
                    // If the symbol is a non-terminal, compute its First set
                    computeFirst(symbol);
                    first[nonTerminal].insert(first[symbol].begin(), first[symbol].end());
                    // If a non-terminal produces ε, continue with the next symbol
                    if (first[symbol].count('ε') == 0) break;
                } else {
                    // If the symbol is a terminal, add it to the First set
                    first[nonTerminal].insert(symbol);
                    break;
                }
            }
        }
    }
}

// Function to compute the Follow set for a non-terminal
void computeFollow(char nonTerminal) {
    // If already computed, return
    if (!follow[nonTerminal].empty()) return;

    // Base case: Follow(S) contains the end of input symbol
    if (nonTerminal == 'S') follow[nonTerminal].insert('$');

    // Iterate over all productions to find where the non-terminal appears
    for (const auto& prod : productions) {
        for (const string& production : prod.second) {
            for (int i = 0; i < production.size(); i++) {
                if (production[i] == nonTerminal) {
                    // Case 1: Non-terminal is followed by a terminal
                    if (i + 1 < production.size() && !isupper(production[i + 1])) {
                        follow[nonTerminal].insert(production[i + 1]);
                    }
                    // Case 2: Non-terminal is followed by a non-terminal
                    if (i + 1 < production.size() && isupper(production[i + 1])) {
                        computeFirst(production[i + 1]);
                        follow[nonTerminal].insert(first[production[i + 1]].begin(), first[production[i + 1]].end());
                        // If the First set contains ε, add Follow of the non-terminal
                        if (first[production[i + 1]].count('ε') > 0 && i + 1 == production.size()) {
                            computeFollow(prod.first);
                            follow[nonTerminal].insert(follow[prod.first].begin(), follow[prod.first].end());
                        }
                    }
                    // Case 3: Non-terminal is at the end of the production
                    if (i + 1 == production.size() || (i + 1 < production.size() && first[production[i + 1]].count('ε') > 0)) {
                        computeFollow(prod.first);
                        follow[nonTerminal].insert(follow[prod.first].begin(), follow[prod.first].end());
                    }
                }
            }
        }
    }
}

void printSet(const set<char>& s) {
    for (char c : s) {
        cout << c << " ";
    }
    cout << endl;
}

int main() {
    // Define the grammar
    productions['S'] = {"A B C", "D"};
    productions['A'] = {"a", "ε"};
    productions['B'] = {"b", "ε"};
    productions['C'] = {"( S )", "c"};
    productions['D'] = {"A C"};

    // Compute First sets
    for (const auto& prod : productions) {
        computeFirst(prod.first);
    }

    // Compute Follow sets
    for (const auto& prod : productions) {
        computeFollow(prod.first);
    }

    // Output the First and Follow sets
    cout << "First(S) = "; printSet(first['S']);
    cout << "First(A) = "; printSet(first['A']);
    cout << "First(B) = "; printSet(first['B']);
    cout << "First(C) = "; printSet(first['C']);
    cout << "First(D) = "; printSet(first['D']);
    
    cout << "Follow(S) = "; printSet(follow['S']);
    cout << "Follow(A) = "; printSet(follow['A']);
    cout << "Follow(B) = "; printSet(follow['B']);
    cout << "Follow(C) = "; printSet(follow['C']);
    cout << "Follow(D) = "; printSet(follow['D']);

    return 0;
}
