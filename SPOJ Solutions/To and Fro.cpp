/**
 * Problem's url
 * http://www.spoj.com/problems/TOANDFRO/
 */

#include <iostream>
using namespace std;

string recoverMessage (int cols, string encrypted) {
    int rows = encrypted.length () / cols;
    string message = "";
    for (int i=0; i<cols; ++i) {
        for (int j=0; j<rows; j+=2) {
            message += encrypted [cols * j + i];
            if (j < rows - 1)
                message += encrypted [cols * (j + 2) - 1 - i];
        }
    }
    return message;
}

int main () {
    int n;
    while (1) {
        cin >> n;
        if (! n) break;
        string encrypted;
        cin >> encrypted;
        cout << recoverMessage (n, encrypted) << endl;
    }
    return 0;
}
