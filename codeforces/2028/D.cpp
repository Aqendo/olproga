#include <bits/stdc++.h>
#define int int64_t
using namespace std;

void solve() {
    int n;
    cin >> n;
    vector<int> a(n + 1);
    vector<int> b(n + 1);
    vector<int> c(n + 1);
    for (int i = 1; i <= n; ++i) {
        cin >> a[i];
    }
    for (int i = 1; i <= n; ++i) {
        cin >> b[i];
    }
    for (int i = 1; i <= n; ++i) {
        cin >> c[i];
    }
    pair<int, int> aa = {a[1], 1}, bb = {b[1], 1}, cc = {c[1], 1};
    vector<pair<int, int>> prev(n + 1);
    for (int i = 2; i <= n; ++i) {
        bool can = false;
        if (aa.first > a[i]) {
            prev[i] = {0, aa.second};
        } else if (bb.first > b[i]) {
            prev[i] = {1, bb.second};
        } else if (cc.first > c[i]) {
            prev[i] = {2, cc.second};
        }
        if (aa.first > a[i] || bb.first > b[i] || cc.first > c[i]) {
            can = true;
            aa = max(aa, {a[i], i});
            bb = max(bb, {b[i], i});
            cc = max(cc, {c[i], i});
        }
        if (i == n) {
            if (!can) {
                cout << "NO\n";
                return;
            }
            int current = i;
            vector<pair<int, int>> answer;
            while (current > 1) {
                pair<int, int> p = prev[current];
                answer.push_back({p.first, current});
                current = p.second;
            }
            reverse(answer.begin(), answer.end());
            cout << "YES\n";
            cout << answer.size() << '\n';
            for (auto& [u, w] : answer) {
                cout << "qkj"[u] << ' ' << w << '\n';
            }
        }
    }
}

signed main() {
    cin.tie(nullptr)->sync_with_stdio(false);
    int t;
    cin >> t;
    while (t--) solve();
}
