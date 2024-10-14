#include "bits/stdc++.h"
using namespace std;
# define int long long
# ifdef SEREGA
# include "/home/ser/olproga/debug.h"
auto freopen_input_result_ = freopen(INPUT_PATH, "r", stdin);
//  auto freopen_output_result_ = freopen("output.txt", "r", stdout);
# endif

# ifndef SEREGA
# define printf(...)
# define debug(...)
# endif

vector<set<int>> g;
vector<int> topsort, used;
bool has_cycle = false;
void dfs(int x) {
    used[x] = 1;
    if (has_cycle) return;
    for (int i : g[x]) {
        if (!used[i]) {
            dfs(i);
        }
        if (used[i] == 1) {
            cout << -1 << endl;
            exit(0);
        }
    }
    used[x] = 2;
    topsort.push_back(x);
}

int n, m;
vector<pair<int, int>> edges;

bool check(int pref) {
    g.assign(n + 1, {});
    topsort.clear();
    for (int i = 0; i < pref; ++i) {
        g[edges[i].first].insert(edges[i].second);
    }
    used.assign(n + 1, {});
    for (int i = 1; i <= n; ++i) {
        if (!used[i]) {
            dfs(i);
        }
    }
    reverse(topsort.begin(), topsort.end());
    for (int i = 1; i < (int)topsort.size(); ++i) {
        if (!g[topsort[i - 1]].contains(topsort[i])) {
            return false;
        }
    }
    return true;
}

void solve() {
    cin >> n >> m;
    edges.assign(m, {});
    for (int i = 0; i < m; ++i) {
        cin >> edges[i].first >> edges[i].second;
    }
    g.assign(n + 1, {});
    for (int i = 0; i < m; ++i) {
        g[edges[i].first].insert(edges[i].second);
    }
    used.assign(n + 1, {});
    for (int i = 1; i <= n; ++i) {
        if (!used[i]) {
            dfs(i);
        }
    }
    reverse(topsort.begin(), topsort.end());
    for (int i = 1; i < (int)topsort.size(); ++i) {
        if (!g[topsort[i - 1]].contains(topsort[i])) {
            cout << -1 << endl;
            return;
        }
    }
    int l = 0, r = m;
    while (r - l > 1) {
        int m_ = (l + r) >> 1;
        if (!check(m_)) {
            l = m_;
        } else {
            r = m_;
        }
    }
    cout << r << endl;
}

signed main() {
# ifndef SEREGA
    cin.tie(nullptr)->sync_with_stdio(false);
# endif
    solve();
}
