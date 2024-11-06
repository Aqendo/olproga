#include <bits/stdc++.h>
using namespace std;
bool f(int x, int y, int A) {
    return (!(x < A) | (x * x < 100)) && (!(y * y <= 64) || (y <= A));
}
int main() {
    int cnt = 0;
    for (int A = -130; A <= 130; ++A) {
        bool good = true;
        for (int x = 0; x < 130; ++x) {
            for (int y = 0; y < 130; ++y) {
                if (!f(x, y, A)) {
                    good = false;
                    break;
                }
            }
            if (!good) break;
        }
        cnt += good;
    }
    cout << cnt << endl;
}