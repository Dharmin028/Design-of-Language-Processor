#include <iostream>
#include <map>
#include <vector>
#include <string>
using namespace std;

int main() {
    int numSymbols, numStates, startState, numAcceptStates;
    vector<char> symbols;
    vector<int> acceptStates;
    map<pair<int, char>, int> transition;

    // Input symbols
    cout << "Number of input symbols: ";
    cin >> numSymbols;
    cout << "Input symbols: ";
    for (int i = 0; i < numSymbols; i++) {
        char sym;
        cin >> sym;
        symbols.push_back(sym);
    }

    // Input states
    cout << "Enter number of states: ";
    cin >> numStates;

    // Initial state
    cout << "Initial state: ";
    cin >> startState;

    // Accepting states
    cout << "Number of accepting states: ";
    cin >> numAcceptStates;
    cout << "Accepting states: ";
    for (int i = 0; i < numAcceptStates; i++) {
        int state;
        cin >> state;
        acceptStates.push_back(state);
    }

    // Transition table
    cout << "Transition table:" << endl;
    for (int s = 1; s <= numStates; s++) {
        for (char sym : symbols) {
            int toState;
            cout << s << " to " << sym << " -> ";
            cin >> toState;
            transition[{s, sym}] = toState;
        }
    }

    // Input string
    string input;
    cout << "Input string: ";
    cin >> input;

    // Run DFA
    int currentState = startState;
    for (char ch : input) {
        if (transition.find({currentState, ch}) != transition.end()) {
            currentState = transition[{currentState, ch}];
        } else {
            cout << "Invalid string" << endl;
            return 0;
        }
    }

    // Check if current state is accepting
    bool isAccepted = false;
    for (int state : acceptStates) {
        if (currentState == state) {
            isAccepted = true;
            break;
        }
    }

    if (isAccepted)
        cout << "Valid string" << endl;
    else
        cout << "Invalid string" << endl;

    return 0;
}
