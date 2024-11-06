#include <bits/stdc++.h>
using namespace std;
bool f(int x, int A) {
    return !(x % A == 0) || ((int)(x % 21 == 0) + (int)(x % 35 == 0));
}
int main() {
    for (int A = 1; A < 10000; ++A) {
        bool good = true;
        for (int x = 1; x < 500; ++x) {
            if (!f(x, A)) {
                good = false;
                break;
            }
        }
        if (good) {
            cout << A << endl;
            return 0;
        }
    }
}