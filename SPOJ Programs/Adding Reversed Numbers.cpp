/**
 * Problem's url
 * http://www.spoj.com/problems/ADDREV/
 */

#include <iostream>
using namespace std;
 
int reverse (int num) {
	int rev = 0;
	while (num != 0) {
		rev *= 10;
		rev += (num % 10);
		num /= 10;
	}
	return rev;
}
 
int main () {
	int t;
	cin >> t;
	while (t--) {
		int a, b;
		cin >> a >> b;
		cout << reverse (reverse (a) + reverse (b)) << endl;
	}
	return 0;
} 
