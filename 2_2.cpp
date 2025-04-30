#include <iostream>
using namespace std;

bool validate(string s) {
    if (s.empty()) return false;
    char start = s[0];
    char end = s[s.length() - 1];

    for (char ch : s) {
        if (ch != 'a' && ch != 'b' && ch != 'c') return false;
    }

    return start == end;
}

int main() {
    string input;
    cout << "Enter string over {a, b, c}: ";
    cin >> input;

    if (validate(input))
        cout << "Valid string" << endl;
    else
        cout << "Invalid string" << endl;

    return 0;
}
