#include <bits/stdc++.h>
using namespace std;
#define int int64_t

const int MOD = 1e9 + 7;

int binpow(int a, int p) {
    int res = 1;
    while (p) {
        if (p & 1) {
            (res *= a) %= MOD;
        }
        (a *= a) %= MOD;
        p >>= 1;
    }
    return res;
}

const int N = 2e5 + 78;

int fact[N], inv[N], a[N];
int C(int n, int k) {
    if (n - k < 0) return 0;
    if (n == k) return 1;
    if (k == 0) return 1;
    return fact[n] * inv[k] % MOD * inv[n - k] % MOD;
}
void solve() {
    fact[1] = 1;
    inv[1] = 1;
    for (int i = 2; i < N; ++i) {
        (fact[i] = fact[i - 1] * i) %= MOD;
        inv[i] = binpow(fact[i], MOD - 2);
    }
    int n;
    cin >> n;
    for (int i = 1; i <= n; ++i) {
        cin >> a[i];
    }
    int first = 0;
    int second = 0;
    int timer = 0;
    int row = (n - 2) / 2;
    for (int i = 1; i <= n; i += 2) {
        int cnt = C(row, timer);
        (first += cnt * a[i]) %= MOD;
        (second += cnt * a[i + 1]) %= MOD;
        timer += 1;
    }
    cout << first << ' ' << second << '\n';
}

signed main() {
    cin.tie(nullptr)->sync_with_stdio(false);
    int t = 1;
    // cin >> t;
    while (t--) solve();
}
