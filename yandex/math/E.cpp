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
    long long A, M;
    cin >> A >> M;
    long long a = A, b = M, c = 1;
    if (c % gcd(a, b) != 0) {
        cout << "-1\n";
        return;
    }
    long long x, y;
    long long g = gcd(a, b, x, y);
    // cout << g << endl;
    // cout << x << ' ' << y << endl;
    long long answer_x = x * c / g;
    cout << (answer_x % M + M) % M << endl;
    return;
}

int main() {
    cin.tie(nullptr)->sync_with_stdio(false);
    solve();
}
