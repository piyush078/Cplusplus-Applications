/**
 * Problem's url
 * http://www.spoj.com/problems/PRIME1/
 */

#include <iostream>
#include <cmath>
#include <vector>
using namespace std;

vector <int> makeSieve (int limit) {
    vector <bool> sieve (limit + 1, true);
    for (int i=2; i*i<limit; ++i) {
        if (sieve [i]) {
            for (int j=i*2; j<limit; j+=i)
                sieve [j] = false;
        }
    }
    vector <int> primes;
    for (int i=2; i<limit; ++i) {
        if (sieve [i]) primes.push_back (i);
    }
    return primes;
}

vector <int> generatePrimes (int m, int n) {
    int limit = floor (sqrt (n)) + 1;
    vector <int> primes = makeSieve (limit), ans;
    vector <bool> sieve (n-m+1, true);
    for (int &ele: primes) {
        if (ele >= m && ele <= n) ans.push_back (ele);
    }
    
    if (m == 1) ++m;
    for (int i=0; i<primes.size (); ++i) {
        int start = floor (m / primes [i]) * primes [i];
        if (start < m) start += primes [i];
        for (int j=start; j<n; j+=primes [i]) {
            sieve [j - m] = false;
        }
    }
    for (int i=m; i<n; ++i) {
        if (sieve [i - m]) ans.push_back (i);
    }
    return ans;
}

int main () {
    int t, m, n;
    cin >> t;
    while (t--) {
        cin >> m >> n;
        vector <int> ans = generatePrimes (m, n + 1);
        for (int &ele:ans) cout << ele << endl;
        cout << endl;
    }
    return 0;
}
