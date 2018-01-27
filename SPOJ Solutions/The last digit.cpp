/**
 * Problem's url
 * http://www.spoj.com/problems/LASTDIG/
 */

#include <iostream>
using namespace std;

int lastDigit (unsigned long &a, unsigned long &b) {
    if (b == 0) return 1;
    int rem = b % 4, ans = 1;
    if (rem == 0) rem = 4;
    while (rem --) {
        ans *= a;
    }
    return ans % 10;
}

int main () {
    int t;
    cin >> t;
    while (t--) {
        unsigned long a, b;
        cin >> a >> b;
        cout << lastDigit (a, b) << endl;
    }
    return 0;
}
