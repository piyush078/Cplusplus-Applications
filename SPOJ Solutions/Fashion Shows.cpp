/**
 * Problem's url
 * http://www.spoj.com/problems/FASHION/
 */

#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int maximizeHotness (vector <int> &men, vector <int> &women) {
    sort (men.begin (), men.end ());
    sort (women.begin (), women.end ());
    int res = 0;
    for (int i=0; i<men.size (); ++i) {
        res += (men [i] * women [i]);
    }
    return res;
}

int main () {
    int t, n;
    cin >> t;
    while (t--) {
        cin >> n;
        vector <int> men (n), women (n);
        for (int i=0; i<n; ++i) cin >> men [i];
        for (int i=0; i<n; ++i) cin >> women [i];
        cout << maximizeHotness (men, women) << endl;
    }
    return 0;
}
