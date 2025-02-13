#include <bits/stdc++.h>
using namespace std;
#define int int64_t

const int N = 1e6 + 78;

int a[N];
int n, k;

vector<int> fact[N];
int lp[N];
int s[N];
vector<int> pr;

int f(int mx) {
    int left = k;
    for (int i = 0; i < n; ++i) {
        int mn = INT_MAX;
        if (a[i] <= mx) continue;
        for (int j : fact[i]) {
            if (a[i] / j <= mx) {
                mn = min(mn, s[j]);
            }
        }
        if (mn <= left) {
            left -= mn;
        } else {
            return false;
        }
    }
    return true;
}

void solve() {
    cin >> n >> k;
    for (int i = 2; i < N; ++i) {
        if (lp[i] == 0) {
            lp[i] = i;
            pr.push_back(i);
        }
        int val = i;
        while (val > 1) {
            s[i] += lp[val];
            val /= lp[val];
        }
        for (int j = 0; j < (int)pr.size() && pr[j] <= lp[i] && i * pr[j] < N; ++j) {
            lp[i * pr[j]] = pr[j];
        }
    }
    for (int i = 0; i < n; ++i) {
        cin >> a[i];
        for (int j = 1; j * j <= a[i]; ++j) {
            if (a[i] % j == 0) {
                fact[i].push_back(j);
                if (a[i] / j != j) {
                    fact[i].push_back(a[i] / j);
                }
            }
        }
    }
    int l = 0, r = 1e6 + 1;
    while (r - l > 1) {
        int mid = (l + r) >> 1;
        if (f(mid)) {
            r = mid;
        } else {
            l = mid;
        }
    }
    cout << r << '\n';
}

signed main() {
    cin.tie(nullptr)->sync_with_stdio(false);
    int t = 1;
    // cin >> t;
    while (t--) solve();
}
