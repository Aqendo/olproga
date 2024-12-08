#include <bits/stdc++.h>
using namespace std;

struct Fenwick {
    vector<int> tree;
    Fenwick(int n) : tree(n + 1) {
    }
    void add(int r, int v) {
        for (; r < tree.size(); r = (r | (r + 1))) {
            tree[r] = max(tree[r], v);
        }
    }
    int get(int r) {
        int answer = INT_MIN;
        for (; r > 0; r = (r & (r + 1)) - 1) {
            answer = max(tree[r], answer);
        }
        return answer;
    }
};

void solve() {
    int g;
    cin >> g;
    int n, q;
    cin >> n >> q;
    vector<int> a(n);
    vector<vector<int>> occurences(n + 2);
    for (int i = 0; i < n; ++i) {
        cin >> a[i];
        occurences[a[i]].push_back(i);
    }
    for (int i = 0; i <= n + 1; ++i) {
        reverse(occurences[i].begin(), occurences[i].end());
    }
    Fenwick fenw(n + 3);
    for (int i = 1; i <= n; ++i) {
        if (!occurences[i].empty()) {
            fenw.add(i, occurences[i].back());
        } else {
            fenw.add(i, INT_MAX);
        }
    }
    vector<vector<int>> pairs(n);
    int additions = 0;
    for (int l = 0; l < n; ++l) {
        int now_size = 1;
        int res = fenw.get(now_size);
        while (res != INT_MAX && l + now_size - 1 < n) {
            while (res - l + 1 > now_size && res != INT_MAX) {
                now_size = res - l + 1;
                res = fenw.get(now_size);
            }
            if (res == INT_MAX) {
                continue;
            }
            pairs[l].push_back(now_size);
            now_size++;
            if (l + now_size - 1 < n) {
                res = fenw.get(now_size);
            }
        }
        occurences[a[l]].pop_back();
        if (occurences[a[l]].empty()) {
            fenw.add(a[l], INT_MAX);
        } else {
            fenw.add(a[l], occurences[a[l]].back());
        }
    }
    for (int i = 0; i < n; ++i) {
        sort(pairs[i].begin(), pairs[i].end());
    }
    for (int i = 0; i < q; ++i) {
        int l, x;
        cin >> l >> x;
        l--;
        auto it = lower_bound(pairs[l].begin(), pairs[l].end(), x);
        if (it == pairs[l].end()) {
            cout << "-1 0\n";
            continue;
        }
        cout << *it << ' ' << pairs[l].end() - it << '\n';
    }
}

signed main() {
    cin.tie(nullptr)->sync_with_stdio(false);
    int t = 1;
    // cin >> t;
    while (t--) solve();
}