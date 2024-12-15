#pragma GCC optimize("Ofast")
#include <bits/stdc++.h>
using namespace std;

vector<vector<int>> phones;
vector<vector<pair<int, int>>> otls;

struct MST {
    vector<vector<int>> tree;
    void init(vector<pair<int, int>>& arr) {
        tree.resize(2 * (int)arr.size());
        build(arr, 0, 0, (int)arr.size() - 1);
    }
    void build(vector<pair<int, int>>& arr, int x, int lx, int rx) {
        if (lx > rx) return;
        if (lx == rx) {
            tree[x] = {arr[lx].first};
            return;
        }
        int m = (lx + rx) >> 1;
        build(arr, x + 1, lx, m);
        build(arr, x + 2 * (m - lx + 1), m + 1, rx);
        tree[x].resize(tree[x + 1].size() + tree[x + 2 * (m - lx + 1)].size());
        merge(tree[x + 1].begin(), tree[x + 1].end(), tree[x + 2 * (m - lx + 1)].begin(), tree[x + 2 * (m - lx + 1)].end(), tree[x].begin());
    }
    int get(int x, int lx, int rx, int l, int r, int less_than) {
        if (l > r || lx > rx) return 0;
        if (l == lx && r == rx) {
            int cnt = lower_bound(tree[x].begin(), tree[x].end(), less_than) - tree[x].begin();
            return cnt;
        }
        int m = (lx + rx) >> 1;
        int s1 = get(x + 1, lx, m, l, min(m, r), less_than);
        int s2 = get(x + 2 * (m - lx + 1), m + 1, rx, max(m + 1, l), r, less_than);
        return s1 + s2;
    }
};

void solve() {
    int n, m, g;
    cin >> n >> m >> g;
    otls.resize(n + 1);
    phones.resize(m + 1);  // otlichie: [phone1, phone2, phone3, ...]
    for (int i = 1; i <= n; ++i) {
        int c;
        cin >> c;
        for (int j = 1; j <= c; ++j) {
            int t;
            cin >> t;
            phones[t].push_back(i);
            otls[i].push_back({t, (int)phones[t].size() - 1});
        }
    }
    vector<MST> msts(n + 1);
    vector<vector<pair<int, int>>> borders(n + 1);
    for (int phone = 1; phone <= n; ++phone) {
        borders[phone].resize(otls[phone].size());
        for (int i = 0; i < (int)otls[phone].size(); ++i) {
            int diff = otls[phone][i].first, index = otls[phone][i].second;
            borders[phone][i] = {INT_MIN, INT_MAX};
            if ((int)phones[diff].size() != index + 1) {
                borders[phone][i].second = phones[diff][index + 1];
            }
            if (index != 0) {
                borders[phone][i].first = phones[diff][index - 1];
            }
        }
        sort(borders[phone].begin(), borders[phone].end(), [](auto& l, auto& r) {
            if (l.second != r.second) return l.second < r.second;
            return l.first < r.first;
        });
        msts[phone].init(borders[phone]);
    }
    int q;
    cin >> q;
    for (int i = 0; i < q; ++i) {
        int l, r, p;
        cin >> l >> r >> p;
        auto it_from = lower_bound(borders[p].begin(), borders[p].end(), r + 1, [](pair<int, int>& ll, const int value) { return ll.second < value; });
        if (it_from - borders[p].begin() == (int)borders[p].size()) {
            cout << 0 << "\n";
            continue;
        }
        int index_from = (it_from - borders[p].begin());
        cout << msts[p].get(0, 0, (int)borders[p].size() - 1, index_from, (int)borders[p].size() - 1, l) << '\n';
    }
}

signed main() {
    cin.tie(nullptr)->sync_with_stdio(false);
    int t = 1;
    // cin >> t;
    while (t--) solve();
}