#include <compare>
#include "bits/stdc++.h"

using namespace std;

#ifdef SEREGA
#include "../debug.h"
auto freopen_input_result_ = freopen("input.txt", "r", stdin);
// auto freopen_output_result_ = freopen("output.txt", "r", stdout);
#endif

vector<vector<int>> g;
vector<int> M;
vector<int> used;
vector<int> order, w;
int n, m;

bool try_kuhn(int a) {
    if (used[a]) return false;
    used[a] = true;
    for (int b : g[a]) {
        if (M[b] == -1 || try_kuhn(M[b])) {
            M[b] = a;
            return true;
        }
    }
    return false;
}

void kuhn() {
    for (int i : order) {
        used.assign(n + m + 1, {});
        try_kuhn(i);
    }
}

void init() {
    g.assign(n + m + 1, {});
    w.assign(n + m + 1, {});
    order.assign(n, {});
    iota(order.begin(), order.end(), 0);
    M.assign(n + m + 1, -1);
}

void solve() {
    cin >> n;
    init();
    for (int i = 0; i < n; ++i) {
        cin >> w[i];
    }
    for (int i = 0; i < n; ++i) {
        int c;
        cin >> c;
        for (int j = 0; j < c; ++j) {
            int v;
            cin >> v;
            v--;
            g[i].push_back(v);
        }
    }
    sort(order.begin(), order.end(), [](int i, int j) { return w[i] > w[j]; });
    kuhn();
    vector<int> verticies(n);
    for (int i = 0; i < n; ++i) {
        if (M[i] != -1) {
            verticies[M[i]] = i + 1;
        }
    }
    for (int i : verticies) {
        cout << i << ' ';
    }
}

signed main() {
    cin.tie(nullptr)->sync_with_stdio(false);
    solve();
}