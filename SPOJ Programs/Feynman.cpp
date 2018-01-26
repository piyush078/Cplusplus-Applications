/**
 * Problem's url
 * http://www.spoj.com/problems/SAMER08F/
 */

#include <iostream>
using namespace std;

long long numberOfSquares (int n) {
    return n * (n + 1) * (2 * n + 1) / 6;
}

int main () {
    int n;
    while (1) {
        cin >> n;
        if (! n) break;
        cout << numberOfSquares (n) << endl;
    }
    return 0;
}
