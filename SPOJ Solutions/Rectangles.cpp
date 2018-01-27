/**
 * Problem's url
 * http://www.spoj.com/problems/AE00/
 */

#include <iostream>
using namespace std;

int numberOfBoxes (int n) {
    int sum = 0;
    for (int i=1; i*i<=n; ++i) {
        sum += (n / i) - (i - 1);
    }
    return sum;
}

int main () {
    int n;
    cin >> n;
    cout << numberOfBoxes (n);
    return 0;
}
