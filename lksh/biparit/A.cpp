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
    for (int i = 0; i < n; ++i) {
        used.assign(n + m + 1, {});
        try_kuhn(i);
    }
}

void init() {
    g.assign(n + m + 1, {});
    M.assign(n + m + 1, -1);
}

void solve() {
    cin >> n >> m;
    init();
    for (int i = 0; i < n; ++i) {
        int x;
        cin >> x;
        x--;
        while (x != -1) {
            g[i].push_back(x);
            cin >> x;
            x--;
        }
    }
    kuhn();
    vector<pair<int, int>> edges;
    for (int i = 0; i < n + m + 1; ++i) {
        if (M[i] != -1) {
            edges.emplace_back(M[i], i);
        }
    }
    cout << edges.size() << '\n';
    for (auto& i : edges) {
        cout << i.first + 1 << ' ' << i.second + 1 << '\n';
    }
}

signed main() {
    cin.tie(nullptr)->sync_with_stdio(false);
    solve();
}