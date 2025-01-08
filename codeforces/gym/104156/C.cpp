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
    for (int i = 1; i <= n; ++i) {
        cin >> a[i];
    }
    a[0] = INF;
    a[n + 1] = INF;
    build();
    for (int i = 0; i < q; ++i) {
        int p, k, answer = 0;
        cin >> p >> k;
        if (k == 1) {
            cout << 1 << '\n';
            continue;
        }
        if (p + k - 1 <= n) {
            auto [mx, index_mx] = get(p, p + k - 1);
            auto [smx1, index_smx1] = get(p, index_mx - 1);
            auto [smx2, index_smx2] = get(index_mx + 1, p + k - 1);
            // cout << p << ' ' << k << ", 1: " << mx << ' ' << index_mx << ' ' << smx << ' ' << index_smx << endl;
            if (smx1 > smx2 && a[p + k] > a[p]) {
                // cout << "+=1\n";
                answer += 1;
            }
            if (p + k >= n || a[p + k] > mx) {
                // cout << "+= " << p + k - 1 - index_mx << endl;
                answer += p + k - 1 - index_mx;
            }
        }
        if (p - k >= 1) {
            auto [mx, index_mx] = get(p - k + 1, p);
            auto [smx1, index_smx1] = get(p - k + 1, index_mx - 1);
            auto [smx2, index_smx2] = get(index_mx + 1, p);
            // cout << p << ' ' << k << ", 2: " << mx << ' ' << index_mx << ' ' << smx << ' ' << index_smx << endl;
            if (smx2 > smx1 && (p - k < 0 || a[p - k] > a[p])) {
                // cout << "+=1\n";
                answer += 1;
            }
            if (p - k < 0 || a[p - k] > mx) {
                answer += index_mx - 1 - (p - k);
            }
        }
        // cout << "ANSWER: ";
        cout << answer << '\n';
    }
}

signed main() {
    plg[1] = 0;
    for (int i = 2; i < N; ++i) {
        plg[i] = plg[i >> 1] + 1;
    }
    cin.tie(nullptr)->sync_with_stdio(false);
    int t = 1;
    // cin >> t;
    while (t--) solve();
}