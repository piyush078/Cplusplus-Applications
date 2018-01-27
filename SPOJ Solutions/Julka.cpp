/**
 * Problem's url
 * http://www.spoj.com/problems/JULKA/
 */

#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

vector <int> toArray (string str) {
    vector <int> array (str.length ());
    for (int i=0; i<str.length (); ++i) {
        array [i] = str [i] - '0';
    }
    return array;
}

vector <int> division (const vector <int> &num) {
    vector <int> res;
    int carry = 0, div;
    for (int i=0; i<num.size (); ++i) {
        div = carry * 10 + num [i];
        if (i || div / 2) res.push_back (div / 2);
        carry = div % 2;
    }
    return res;
}

vector <int> addition (const vector <int> &a, const vector <int> &b) {
    vector <int> res;
    int i = 0, sum, carry = 0;
    while (i < b.size () || i < a.size () || carry) {
        sum = carry;
        if (i < a.size ()) sum += a [a.size () - (i + 1)];
        if (i < b.size ()) sum += b [b.size () - (i + 1)];
        res.push_back (sum % 10);
        carry = sum / 10;
        ++i;
    }
    
    reverse (res.begin (), res.end ());
    return res;
}

vector <int> subtraction (const vector <int> &a, const vector <int> &b) {
    vector <int> res;
    int i = 0, it, from;
    bool borrow = false;
    while (i < a.size () || i < b.size ()) {
        from = a [a.size () - (i + 1)];
        if (i < b.size ()) it = b [b.size () - (i + 1)];
        else it = 0;
        
        if (borrow) {
            if (from == 0) borrow = true;
            else borrow = false;
            from = borrow ? 9 : from - 1;
        }
        if (from < it) {
            borrow = true;
            from = 10 + from;
        }
        res.push_back (from - it);
        ++i;
    }

    while (res [res.size () - 1] == 0) res.pop_back ();
    if (res.size () == 0) res.push_back (0);
    reverse (res.begin (), res.end ());
    return res;
}

int main () {
    int t = 10;
    string total, diff;
    while (t--) {
        cin >> total >> diff;
        vector <int> totalNumber = toArray (total);
        vector <int> diffNumber = toArray (diff);
        vector <int> klaudia = division (addition (totalNumber, diffNumber));
        vector <int> natalia = division (subtraction (totalNumber, diffNumber));
        for (int &digit: klaudia) cout << digit;
        cout << endl;
        for (int &digit: natalia) cout << digit;
        cout << endl;
    }
    return 0;
}
