/**
 * Problem's url
 * http://www.spoj.com/problems/EIGHTS/
 */

#include <iostream>
using namespace std;

int main () {
	long long t, n, k;
	cin >> t;
	while (t--) {
		cin >> k;
		cout << (192 + (k - 1) * 250) << endl;
	}
	return 0;
}
