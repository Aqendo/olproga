#include <bits/stdc++.h>
using namespace std;
#define int int64_t

const int LG = 18, N = 1e5 + 78, INF = 1e18;

pair<int, int> sparse[LG][N];
int a[N], plg[N];

int n, q;

void build() {
    for (int i = 0; i < n; ++i) {
        sparse[0][i] = {a[i], i};
    }
    for (int lg = 1; lg < LG; ++lg) {
        for (int i = 0; i < n; ++i) {
            sparse[lg][i] = sparse[lg - 1][i];
            if (i + (1 << (lg - 1)) < n) {
                sparse[lg][i] = max(sparse[lg][i], sparse[lg - 1][i + (1 << (lg - 1))]);
            }
        }
    }
}

pair<int, int> get(int l, int r) {
    if (l > r) return {-INF, 1};
    const int lg = plg[r - l + 1];
    return max(sparse[lg][l], sparse[lg][r - (1 << lg) + 1]);
}

void solve() {
    cin >> n >> q;
    for (int i = 0; i < n; ++i) {
        cin >> a[i];
    }
    build();
    for (int i = 0; i < q; ++i) {
        int p, k, answer = 0;
        cin >> p >> k;
        p--;
        if (k == 1) {
            cout << 1 << '\n';
            continue;
        }
        if (p + k - 1 < n) {
            auto [mx, index_mx] = get(p + 1, p + k - 1);
            auto [smx, index_smx] = max(get(p, index_mx - 1), get(index_mx + 1, p + k - 1));
            cout << p << ' ' << k << ", 1: " << mx << ' ' << index_mx << ' ' << smx << ' ' << index_smx << endl;
            if (smx == a[i] && a[i] < mx && (p + k >= n || a[p + k] > mx)) {
                answer += 1;
            }
            if (p + k >= n || a[p + k] > a[p]) {
                answer += p + k - 1 - index_mx;
            }
        }
        if (p - k + 1 >= 0) {
            auto [mx, index_mx] = get(p - k + 1, p - 1);
            auto [smx, index_smx] = max(get(p - k + 1, index_mx - 1), get(index_mx + 1, p - 1));
            cout << p << ' ' << k << ", 2: " << mx << ' ' << index_mx << ' ' << smx << ' ' << index_smx << endl;
            if (smx == a[i] && a[i] < mx && (p - k < 0 || a[p - k] > mx)) {
                answer += 1;
            }
            if (p - k < 0 || a[p - k] > a[p]) {
                answer += index_mx - (p - k);
            }
        }
        cout << answer << '\n';
    }
}

signed main() {
    plg[1] = 0;
    for (int i = 0; i < N; ++i) {
        plg[i] = plg[i >> 1] + 1;
    }
    cin.tie(nullptr)->sync_with_stdio(false);
    int t = 1;
    // cin >> t;
    while (t--) solve();
}