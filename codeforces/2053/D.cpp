#include <bits/stdc++.h>
using namespace std;
#define int int64_t
const int MOD = 998'244'353;
int binpow(int x, int p) {
    int res = 1;
    while (p) {
        if (p & 1) {
            res *= x;
            res %= MOD;
        }
        x *= x;
        x %= MOD;
        p /= 2;
    }
    return res;
}
int inv(int x) {
    return binpow(x, MOD - 2);
}
void solve() {
    int n, q;
    cin >> n >> q;
    vector<int> a(n), b(n);
    for (int i = 0; i < n; ++i) {
        cin >> a[i];
    }
    for (int i = 0; i < n; ++i) {
        cin >> b[i];
    }
    vector<int> as = a, bs = b;
    vector<int> ai(n), bi(n);
    iota(ai.begin(), ai.end(), 0);
    iota(bi.begin(), bi.end(), 0);
    sort(ai.begin(), ai.end(), [&a](int i, int j) {
        return a[i] < a[j];
    });
    sort(bi.begin(), bi.end(), [&b](int i, int j) {
        return b[i] < b[j];
    });
    vector<int> reva(n), revb(n);
    sort(as.begin(), as.end());
    sort(bs.begin(), bs.end());
    for (int i = 0; i < n; ++i) {
        reva[ai[i]] = i;
        revb[bi[i]] = i;
    }

    int answer = 1;
    for (int i = 0; i < n; ++i) {
        answer *= min(as[i], bs[i]);
        answer %= MOD;
    }
    cout << answer << ' ';
    while (q--) {
        int move, x;
        cin >> move >> x;
        x--;

        if (move == 1) {
            // a[x] += 1;
            int r = upper_bound(as.begin(), as.end(), a[x]) - as.begin() - 1;
            if (min(as[r], bs[r]) != min(as[r] + 1, bs[r])) {
                int d = min(as[r], bs[r]);
                answer = (answer + (answer * inv(d) % MOD)) % MOD;
            }
            a[x]++;
            as[r]++;
            // (x, index_swapped_in_orig)
            swap(ai[reva[x]], ai[reva[ai[r]]]);
            swap(reva[x], reva[ai[r]]);
        } else {
            // a[x] += 1;
            int r = upper_bound(bs.begin(), bs.end(), b[x]) - bs.begin() - 1;
            if (min(as[r], bs[r]) != min(as[r], bs[r] + 1)) {
                int d = min(as[r], bs[r]);
                answer = (answer + (answer * inv(d) % MOD)) % MOD;
            }
            b[x]++;
            bs[r]++;
            // (x, index_swapped_in_orig)
            swap(bi[revb[x]], bi[revb[bi[r]]]);
            swap(revb[x], revb[bi[r]]);
        }
        cout << answer << ' ';
    }

    // for (int i : a) {
    //     cout << i << ' ';
    // }
    // cout << endl;
    // for (int i : as) {
    //     cout << i << ' ';
    // }
    // cout << endl;
    // for (int i : ai) {
    //     cout << i << ' ';
    // }
    // cout << endl;
    // for (int i : reva) {
    //     cout << i << ' ';
    // }
    // cout << endl;
    cout << '\n';
}

signed main() {
    cin.tie(nullptr)->sync_with_stdio(false);
    int t = 1;
    cin >> t;
    while (t--) solve();
}