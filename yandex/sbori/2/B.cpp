#include <bits/stdc++.h>
using namespace std;
#define int int64_t
const int MOD = 1e9 + 7;
int binpow(int x, int p) {
    int res = 1;
    while (p) {
        if (p & 1) {
            res *= x;
            res %= MOD;
            p--;
        } else {
            x *= x;
            x %= MOD;
            p >>= 1;
        }
    }
    return res;
}
const int MAXN = 2e5 + 78;
int fact[MAXN];
int inv(int x) {
    return binpow(x, MOD - 2);
}
int C(int n, int k) {
    // cout << "C: " << n << ' ' << k << endl;
    if (n == k) return 1;
    if (k > n || k == 0 || n == 0) return 0;
    int res = fact[n] * inv(fact[k] * fact[n - k] % MOD) % MOD;
    // cout << res << endl;
    return res;
}
int sub(int a, int b) {
    return a - b < 0 ? a - b + MOD : a - b;
}
void solve() {
    int n;
    cin >> n;
    vector<int> a(n);
    map<int, int> cnt;
    int mx = 0;
    for (int i = 0; i < n; ++i) {
        cin >> a[i];
        cnt[a[i]]++;
        mx = max(mx, cnt[a[i]]);
    }
    vector<pair<int, int>> cntv(cnt.begin(), cnt.end());
    int answer = 0;
    int wholes = 0;
    for (int grab = 1; grab <= mx; ++grab) {
        int m = -1;
        for (int i = 0; i < (int)cntv.size(); ++i) {
            if (cntv[i].second >= grab) {
                if (m == -1) {
                    m = C(cntv[i].second, grab) + 1;
                    m %= MOD;
                } else {
                    m *= C(cntv[i].second, grab) + 1;
                    m %= MOD;
                }
            }
        }
        if (m != -1) {
            answer += sub(m, 1);
            answer %= MOD;
            wholes++;
        }
    }
    if (wholes) answer++;
    answer %= MOD;
    cout << answer << '\n';
}

signed main() {
    cin.tie(nullptr)->sync_with_stdio(false);
    fact[1] = 1;
    for (int i = 2; i < MAXN; ++i) {
        fact[i] = (fact[i - 1] * i) % MOD;
    }
    int t = 1;
    // cin >> t;
    while (t--) solve();
}