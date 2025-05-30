#include <bits/stdc++.h>
using namespace std;

int g;
int n, q;
vector<int> a;
struct Fenwick {
    vector<int> tree;
    Fenwick(int nn) : tree(nn + 1) {
    }
    void add(int r, int v) {
        for (; r < tree.size(); r = (r | (r + 1))) {
            tree[r] = max(tree[r], v);
        }
    }
    int get(int r) {
        if (r >= tree.size()) {
            cout << g << endl
                 << n << ' ' << q << endl;
            for (int i : a) cout << i << ' ';
            cout << endl;
            exit(0);
        }
        int answer = INT_MIN;
        for (; r > 0; r = (r & (r + 1)) - 1) {
            answer = max(tree[r], answer);
        }
        return answer;
    }
};
void solve() {
    map<int, vector<int>> occurences;
    for (int i = 0; i < n; ++i) {
        occurences[a[i]].push_back(i);
    }
    for (auto &[u, v] : occurences) {
        reverse(v.begin(), v.end());
    }
    Fenwick fenw(n + 3);
    for (int i = 1; i <= n; ++i) {
        if (occurences.find(i) != occurences.end() && !occurences[i].empty()) {
            fenw.add(i, occurences[i].back());
        } else {
            fenw.add(i, INT_MAX);
        }
    }
    map<int, vector<int>> pairs;
    int additions = 0;
    for (int l = 0; l < n; ++l) {
        int now_size = 1;
        int res = fenw.get(now_size);
        while (res != INT_MAX) {
            while (res - l + 1 > now_size && res != INT_MAX) {
                now_size = res - l + 1;
                res = fenw.get(now_size);
            }
            if (res == INT_MAX) {
                continue;
            }
            pairs[l].push_back(now_size);
            now_size++;
            res = fenw.get(now_size);
        }
        occurences[a[l]].pop_back();
        if (occurences[a[l]].empty()) {
            fenw.add(a[l], INT_MAX);
        } else {
            fenw.add(a[l], occurences[a[l]].back());
        }
    }
    for (auto &[u, v] : pairs) {
        sort(v.begin(), v.end());
    }
    return;
    for (int i = 0; i < q; ++i) {
        int l, x;
        cin >> l >> x;
        l--;
        if (pairs.find(l) == pairs.end()) {
            cout << "-1 0\n";
            continue;
        }
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
    mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());
#define uid(x, y) uniform_int_distribution<int>(x, y)(rng)
    while (true) {
        n = uid(1, 30);
        q = 0;
        a.assign(n, {});
        for (int i = 0; i < n; ++i) {
            a[i] = uid(1, n);
        }
        solve();
    }
}