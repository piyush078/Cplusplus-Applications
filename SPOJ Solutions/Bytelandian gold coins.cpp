/**
 * Problem's url
 * http://www.spoj.com/problems/COINS/
 */

#include <iostream>
#include <map>
using namespace std;
map <int, long long> value;

long long exchangeValue (int n) {
    if (n == 0) return 0;
    else if (value.find (n) != value.end ()) return value [n];
    
    long long ans = exchangeValue (n / 2) + exchangeValue (n / 3) + exchangeValue (n / 4);
    if (ans > n) value [n] = ans;
    else value [n] = n;
    return value [n];
}

int main () {
    int n;
    while (cin >> n) {
        cout << exchangeValue (n) << endl;
    }
    return 0;
}
