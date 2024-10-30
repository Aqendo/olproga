#include "bits/stdc++.h"
using namespace std;

void solve() {
    int a, b, c, d;
    cin >> a >> b >> c >> d;
    int answer = 0;
    for (int A = a; A <= b; ++A) {
        for (int B = A; B <= b; ++B) {
            for (int C = B + 1; C <= c; ++C) {
                int D = b - a + d - c - B + A + C;
                if (d <= D) {
                    answer += 1;
                }
            }
        }
    }
    cout << answer << endl;
}

int main() {
    cin.tie(nullptr)->sync_with_stdio(false);
    solve();
}
