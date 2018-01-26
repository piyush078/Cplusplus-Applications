/**
 * Problem's url
 * http://www.spoj.com/problems/ACPC10A/
 */

#include <iostream>
using namespace std;

string typeOfProgression (const int &a, const int &b, const int &c) {
    return (a + c == 2 * b) ? "AP" : "GP";
}

int nextNumber (const int &a, const int &b, const int &c, string type) {
    if (type == "AP") {
        return c + (c - b);
    } else {
        return c * (c / b);
    }
}

int main () {
    int a, b, c;
    while (1) {
        cin >> a >> b >> c;
        if (a == 0 && b == 0 && c == 0) break;
        string type = typeOfProgression (a, b, c);
        cout << type << " ";
        cout << nextNumber (a, b, c, type) << endl;
    }
    return 0;
}
