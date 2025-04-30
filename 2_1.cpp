#include <iostream>
using namespace std;

bool validate(string s) {
    int state = 0; // q0

    for (char ch : s) {
        switch (state) {
            case 0: // q0
                if (ch == '0') state = 1;
                else if (ch == '1') state = 0;
                else return false;
                break;
            case 1: // q1
                if (ch == '1') state = 2;
                else return false; // invalid
                break;
            case 2: // q2
                if (ch == '1') state = 0;
                else return false; // invalid
                break;
            default:
                return false;
        }
    }
    return state == 0;
}

int main() {
    string input;
    cout << "Enter binary string: ";
    cin >> input;

    if (validate(input))
        cout << "Valid string" << endl;
    else
        cout << "Invalid string" << endl;

    return 0;
}
