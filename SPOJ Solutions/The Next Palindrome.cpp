/**
 * Problem's url
 * http://www.spoj.com/problems/PALIN/
 */

#include <iostream>
#include <algorithm>
using namespace std;

string convert (string str) {
    int len = str.length ();
    int half = len / 2;
    for (int i=half; i>=0; --i) {
        str [len - (i + 1)] = str [i];
    }
    return str;
}

bool isLarger (string s, string t) {
    int i = s.length () / 2;
    bool greater = false;
    for (; i<s.length (); ++i) {
        if (t [i] > s [i]) {
            greater = true;
            break;
        } else if (t [i] < s [i]) break;
    }
    return greater;
}

string nextPalindrome (string str) {
    string temp = convert (str);
    if (isLarger (str, temp)) return temp;
    else if (str == "9") return "11";

    int len = str.length (), half = len / 2;
    bool carry = false;

    if (len % 2 == 0) {
        --half;
        if (str [half] > str [half + 1]) {
            str [half + 1] = str [half];
        } else if (str [half] == '9' && str [half + 1] == '9') {
            str [half + 1] = str [half] = '0';
            carry = true;
        } else {
            str [half] = str [half + 1] = str [half] + 1;
        }
    } else {
        if (str [half] == '9') {
            str [half] = '0';
            carry = true;
        } else {
            ++str [half];
        }
    }

    for (int i=half-1; i>=0; --i) {
        if (carry) {
            if (str [i] == '9') {
                str [len - (i + 1)] = str [i] = '0';
            } else {
                str [len - (i + 1)] = str [i] = str [i] + 1;
                carry = false;
            }
        } else {
            str [len - (i + 1)] = str [i];
        }
    }

    if (carry) {
        str [len - 1] = '1';
        return "1" + str;
    } else {
        return str;
    }
}

int main () {
    int t;
    cin >> t;
    while (t--) {
        string str;
        cin >> str;
        cout << nextPalindrome (str) << endl;
    }
    return 0;
}
