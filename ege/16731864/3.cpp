#include <bits/stdc++.h>
using namespace std;
bool f(int x, int A) {
    return ((x & 51) == 0) || (!((x & 41) == 0) || ((x & A) == 0));
}
int main() {
    for (int A = 0; A < 10000; ++A) {
        bool good = true;
        for (int x = 0; x < 500; ++x) {
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