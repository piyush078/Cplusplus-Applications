/**
 * Problem's url
 * http://www.spoj.com/problems/CANDY3/
 */

#include <iostream>
using namespace std;

string isDivisionPossible (long long int n) {
    long long sum = 0, num;
    for (long long int i=0; i<n; ++i) {
        cin >> num;
        sum = (sum + num) % n;
    }
    return sum ? "NO" : "YES";
}

int main () {
    int t;
    cin >> t;
    while (t--) {
        long long n;
        cin >> n;
        cout << isDivisionPossible (n) << endl;
    }
    return 0;
}
