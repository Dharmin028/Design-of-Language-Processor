// Online C++ compiler to run C++ program online
#include <bits/stdc++.h>
using namespace std;

int main() {
    // Write C++ code here
    string s;
    cout<<"ENTER:";
    getline(cin,s);
    
    int i=0;
    
    while(i<s.length() && s[i] == 'a')
    {
        i++;
    }
    
    if(i+1 < s.length() && s[i] == 'b' && s[i+1] == 'b' && i+2 == s.length())
    {
        cout<<"valid"<<endl;
    }
    else
    cout<<"invalid"<<endl;
    
    return 0;
}
