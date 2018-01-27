/**
 * Problem's url
 * http://www.spoj.com/problems/ACODE/
 */

#include <iostream>
#include <vector>
using namespace std;

int numberOfDecodings (string str) {
	vector <int> dp (str.length ()+1);
	dp [0] = 1, dp [1] = 1;
	for (int i=2; i<=str.length (); ++i) {
		dp [i] = 0;
		int c1 = str [i - 2] - '0', c2 = str [i - 1] - '0';
		if (c1 == 1 || (c1 == 2 && c2 <= 6)) dp [i] = dp [i-2];
		if (c2 != 0) dp [i] += dp [i-1];
	}
	return dp [str.length ()];
}

int main () {
	string str;
	while (1) {
		cin >> str;
		if (str == "0") break;
		cout << numberOfDecodings (str) << endl;
	}
	return 0;
}
