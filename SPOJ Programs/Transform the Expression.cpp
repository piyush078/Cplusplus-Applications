/**
 * Problem's url
 * http://www.spoj.com/problems/ONP/
 */

#include <iostream>
#include <stack>
using namespace std;

void addToOutput (stack <char> &s, string &postfix) {
    postfix += s.top ();
    s.pop ();
}

string toPostfix (string infix) {
    stack <char> s;
    string postfix = "";
    
    for (int i=0; i<infix.length (); ++i) {
        if (infix [i] == ')') {
            while (s.top () != '(') addToOutput (s, postfix);
            s.pop ();
        } else if (infix [i] == '(') {
            s.push (infix [i]);
        } else if (infix [i] >= 'a' && infix [i] <= 'z') {
            postfix += infix [i];
        } else {
            if (infix [i] == '+') while (!s.empty () && (s.top () == '-' || s.top () == '*' || s.top () == '/' || s.top () == '^')) addToOutput (s, postfix);
            else if (infix [i] == '-') while (!s.empty () && (s.top () == '*' || s.top () == '/' || s.top () == '^')) addToOutput (s, postfix);
            else if (infix [i] == '*') while (!s.empty () && (s.top () == '/' || s.top () == '^')) addToOutput (s, postfix);
            else if (infix [i] == '/') while (!s.empty () && (s.top () == '^')) addToOutput (s, postfix);
            s.push (infix [i]);
        }
    }
    
    return postfix;
}

int main () {
    string infix;
    int t; cin >> t;
    while (t--) {
        cin >> infix;
        cout << toPostfix (infix) << endl;
    }
    return 0;
}
