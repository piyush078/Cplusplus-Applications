/**
 * Problem's url
 * http://www.spoj.com/problems/FCTRL/
 */

#include <iostream>
using namespace std;

int numberOfZeroes (int n) {
	int count = 0;
	while (n >= 5) {
		count += n / 5;
		n /= 5;
	}
	return count;
}

int main () {
	int t, n;
	cin >> t;
	while (t--) {
		cin >> n;
		cout << numberOfZeroes (n) << endl;
	}
	return 0;
}
