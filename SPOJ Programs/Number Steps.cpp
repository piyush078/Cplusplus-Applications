/**
 * Problem's url
 * http://www.spoj.com/problems/NSTEPS/
 */

#include <iostream>
using namespace std;

int getNumber (const int &x, const int &y) {
    if (x == y) {
        if (x % 2 == 0) return x * 2;
        else return (x + 1) * 2 - 3;
    } else if (x - y == 2) {
        if (x % 2 == 0) return x + (x - 2);
        else return x + (x - 3);
    } else {
        return -1;
    }
}

int main () {
    int t, x, y;
    cin >> t;
    while (t--) {
        cin >> x >> y;
        int result = getNumber (x, y);
        result == -1 ? cout << "No Number" : cout << result;
        cout << endl;
    }
    return 0;
}
