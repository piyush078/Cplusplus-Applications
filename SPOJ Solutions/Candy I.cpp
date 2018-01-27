/**
 * Problem's url
 * http://www.spoj.com/problems/CANDY/
 */

#include <iostream>
#include <vector>
using namespace std;

int abs (int num) {
    return num < 0 ? -num : num;
}

int numberOfMoves (vector <int> candy) {
    int sum = 0;
    for (int &ele: candy) sum += ele;
    if (sum % candy.size ()) return -1;

    int average = sum / candy.size ();
    int res = 0;
    for (int &ele: candy) {
        res += abs (average - ele);
    }
    return res / 2;
}

int main () {
    int n;
    while (1) {
        cin >> n;
        if (n == -1) break;
        vector <int> candy (n);
        for (int i=0; i<n; ++i) cin >> candy [i];
        cout << numberOfMoves (candy) << endl;
    }
    return 0;
}
