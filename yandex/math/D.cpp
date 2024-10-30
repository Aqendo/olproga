#include "bits/stdc++.h"
using namespace std;

long long gcd(long long a, long long b, long long& x, long long& y) {
    if (a == 0) {
        x = 0;
        y = 1;
        return b;
    }
    long long x1, y1;
    long long g = gcd(b % a, a, x1, y1);
    x = y1 - (b / a) * x1;
    y = x1;
    return g;
}

void solve() {
    long long A, B, N, M;
    cin >> A >> B >> N >> M;
    long long a = N, b = -M, c = B - A;
    if (c % gcd(a, b) != 0) {
        cout << "NO\n";
        return;
    }
    long long x, y;
    long long g = gcd(a, b, x, y);
    // cout << g << endl;
    // cout << x << ' ' << y << endl;
    long long answer_N = x * c / g;
    long long x_ = N * answer_N + A;
    long long second = N / gcd(N, M) * M;
    cout << "YES " << ((x_ % second) + second) % second << ' ' << second << '\n';
    return;
}

int main() {
    cin.tie(nullptr)->sync_with_stdio(false);
    int t;
    cin >> t;
    while (t--) solve();
}
