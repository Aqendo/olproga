#include "bits/stdc++.h"
using namespace std;

long long n, m, k;
long long T;
bool can_be(long long a, long long b, long long m1, long long m2) {
    // a + m1 * n + b + m2 * m = 0
    // m1 * n + m2 * m = b - a
    // n, m, b - a
    return (b - a) % gcd(m1, m2) == 0;
}
void solve() {
    cin >> T >> n >> m >> k;
    for (int i = 0; i < T; ++i) {
        long long a1, a2, a3, b1, b2, b3;
        cin >> a1 >> a2 >> a3 >> b1 >> b2 >> b3;
        if (can_be(a1 - b1, b2 - a2, n, m) && can_be(b2 - a2, a3 - b3, m, k) && can_be(a1 - b1, a3 - b3, n, k)) {
            cout << "YES\n";
        } else {
            cout << "NO\n";
        }
    }
}

int main() {
    cin.tie(nullptr)->sync_with_stdio(false);
    solve();
}
