/**
 * Problem's url
 * http://www.spoj.com/problems/HANGOVER/
 */

#include <iostream>
using namespace std;

float numberOfCards (float n) {
    float sum = 0.50, i = 1;
    for (i=1.00f; sum<n; ++i) {
        sum += (1 / (i + 2));
    }
    return i;
}

int main() {
    float n;
    while (1) {
        cin >> n;
        if (n == 0.00f) break;
        cout << numberOfCards (n) << " card(s)" << endl;
    }
    return 0;
}
