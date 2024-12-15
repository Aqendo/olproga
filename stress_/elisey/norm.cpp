#include <cassert>
#include <valarray>

#include "bits/stdc++.h"

using namespace std;

vector<vector<int>> g, gT;
vector<int> topsort;
vector<char> used;
vector<int> condense_num;
vector<set<int>> g_condensed;
vector<vector<int>> indicies_in_topsort;
vector<int> result;

void dfs_topsort(int x) {
    used[x] = true;
    for (int u : g[x]) {
        if (!used[u]) {
            dfs_topsort(u);
        }
    }
    topsort.push_back(x);
}

int cur_comp = 0;

void dfs_condense(int x, int compnumber) {
    used[x] = true;
    indicies_in_topsort[compnumber].push_back(x);
    condense_num[x] = compnumber;
    for (int u : gT[x]) {
        if (!used[u]) {
            dfs_condense(u, compnumber);
        }
    }
}

void add(int l, int r) {
    g[l].push_back(r);
    gT[r].push_back(l);
}

void dfs_get_condensed(int x) {
    used[x] = true;
    for (int u : g[x]) {
        g_condensed[condense_num[x]].insert(condense_num[u]);
        if (!used[u]) {
            dfs_get_condensed(u);
        }
    }
}

void dfs_topsort_condensed(int x) {
    used[x] = true;
    for (int u : g_condensed[x]) {
        assert(u <= cur_comp);
        if (!used[u]) {
            dfs_topsort_condensed(u);
        }
    }
    topsort.push_back(x);
}

void solve() {
    int n;
    while (cin >> n) {
        cur_comp = 0;
        g.assign(2 * n, {});
        gT.assign(2 * n, {});
        int m;
        cin >> m;
        for (int i = 0; i < m; ++i) {
            int i1, e1, i2, e2;
            cin >> i1 >> e1 >> i2 >> e2;
            if (e1 == 0 && e2 == 0) {
                add(i1 << 1, i2 << 1 ^ 1);
                add(i2 << 1, i1 << 1 ^ 1);
            } else if (e1 == 0 && e2 == 1) {
                add(i1 << 1, i2 << 1);
                add(i2 << 1 ^ 1, i1 << 1 ^ 1);
            } else if (e1 == 1 && e2 == 0) {
                add(i2 << 1, i1 << 1);
                add(i1 << 1 ^ 1, i2 << 1 ^ 1);
            } else {
                add(i1 << 1 ^ 1, i2 << 1);
                add(i2 << 1 ^ 1, i1 << 1);
            }
        }
        used.assign(2 * n, {});
        topsort.clear();
        for (int i = 0; i < 2 * n; ++i) {
            if (!used[i]) {
                dfs_topsort(i);
            }
        }
        reverse(topsort.begin(), topsort.end());
        used.assign(2 * n, {});
        condense_num.assign(2 * n, {});
        indicies_in_topsort.assign(1, {});
        for (int i : topsort) {
            if (!used[i]) {
                cur_comp++;
                indicies_in_topsort.push_back({});
                dfs_condense(i, cur_comp);
            }
        }
        g_condensed.assign(cur_comp + 1, {});
        for (int i = 0; i < n; ++i) {
            if (condense_num[i << 1] == condense_num[i << 1 ^ 1] &&
                condense_num[i << 1] != 0) {
                assert(false);
            }
        }
        used.assign(2 * n, {});
        for (int i = 0; i < 2 * n; ++i) {
            if (!used[i]) {
                dfs_get_condensed(i);
            }
        }
        topsort.clear();
        used.assign(cur_comp + 1, {});
        for (int i = 1; i <= cur_comp; ++i) {
            if (!used[i]) {
                dfs_topsort_condensed(i);
            }
        }
        used.assign(cur_comp + 1, {});
        result.assign(2 * n, -1);
        reverse(topsort.begin(), topsort.end());
        for (int i : topsort) {
            if (!used[i]) {
                int to_set = 0;
                for (int j : indicies_in_topsort[i]) {
                    if (result[j ^ 1] == 0) {
                        to_set = 1;
                    }
                    if (result[j ^ 1] == 1 && to_set == 1) {
                        // assert(false);
                    }
                }
                for (int j : indicies_in_topsort[i]) {
                    result[j] = to_set;
                }
            }
        }
        for (int i = 0; i < 2 * n; i += 2) {
            cout << result[i];
        }
        cout << '\n';
    }
}

signed main() {
    cin.tie(nullptr)->sync_with_stdio(false);
    solve();
}