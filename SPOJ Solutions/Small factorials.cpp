/**
 * Problem's url
 * http://www.spoj.com/problems/FCTRL2/
 */

#include <iostream>
#include <vector>
using namespace std;

std::string factorial (int n) {
    vector <int> digits (1, 1);
    int carry = 0;
    for (int i=1; i<=n; ++i) {
        for (int j=0; j<digits.size (); ++j) {
            digits [j] = digits [j] * i + carry;
            carry = digits [j] / 10;
            digits [j] %= 10;
        }
        while (carry) {
            digits.push_back (carry % 10);
            carry /= 10;
        }
    }
    
    string res = "";
    for (int i=digits.size ()-1; i>=0; --i) {
        res += digits [i] + '0';
    }
    return res;
}

int main () {
    int t, n;
    cin >> t;
    while (t--) {
        cin >> n;
        cout << factorial (n) << endl;
    }
    return 0;
}
