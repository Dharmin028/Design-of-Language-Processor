#include <iostream>
using namespace std;

bool validate(string s) {
    if (s.empty()) return false;

    if (!(s[0] >= 'a' && s[0] <= 'z')) return false;

    for (char ch : s) {
        if (!((ch >= 'a' && ch <= 'z') || (ch >= '0' && ch <= '9')))
            return false;
    }

    return true;
}

int main() {
    string input;
    cout << "Enter string with lowercase letters and digits: ";
    cin >> input;

    if (validate(input))
        cout << "Valid string" << endl;
    else
        cout << "Invalid string" << endl;

    return 0;
}
