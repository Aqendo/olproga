# pragma GCC optimize("O3")
#include "bits/stdc++.h"
using namespace std;
# ifdef SEREGA
# include "/home/ser/olproga/debug.h"
auto freopen_input_result_ = freopen(INPUT_PATH, "r", stdin);
//  auto freopen_output_result_ = freopen("output.txt", "r", stdout);
# endif

# ifndef SEREGA
# define printf(...)
# define debug(...)
# endif
int n, m;

vector<vector<int>> a;
vector<vector<int>> g, gT;

vector<int> topsort, used, comp;
vector<vector<int>> g_comp, gT_comp;
vector<int> answer_for_comp;

void get_topsort(int x) {
    used[x] = 1;
    for (int u : g[x]) {
        if (!used[u]) {
            get_topsort(u);
        }
    }
    topsort.push_back(x);
}

void color(int x, int col) {
    used[x] = 1;
    comp[x] = col;
    for (int u : gT[x]) {
        if (!used[u]) {
            color(u, col);
        }
    }
}

void condense(int x) {
    used[x] = 1;
    for (int u : g[x]) {
        if (comp[x] != comp[u]) {
            g_comp[comp[x]].push_back(comp[u]);
            gT_comp[comp[u]].push_back(comp[x]);
        }
        if (!used[u]) {
            condense(u);
        }
    }
}

void topsort_condensed(int x) {
    used[x] = 1;
    for (int u : g_comp[x]) {
        if (!used[u]) {
            topsort_condensed(u);
        }
    }
    topsort.push_back(x);
}

int color_timer = 1;

void solve() {
    cin >> n >> m;
    a.assign(n, vector<int> (m));
    g.assign(n * m, {});
    gT.assign(n * m, {});
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            cin >> a[i][j];
        }
    }
    vector<int> indicies(m);
    iota(indicies.begin(), indicies.end(), 0);
    for (int i = 0; i < n; ++i) {
        sort(indicies.begin(), indicies.end(), [&i](int l, int r) {
            return a[i][l] < a[i][r];
        });
        for (int j = 0; j < m - 1; ++j) {
            int index_first = i * m + indicies[j];
            int index_second = i * m + indicies[j + 1];
            g[index_first].push_back(index_second);
            gT[index_second].push_back(index_first);

            if (a[i][indicies[j]] == a[i][indicies[j + 1]]) {
                g[index_second].push_back(index_first);
                gT[index_first].push_back(index_second);
            }
        }
    }
    indicies.assign(n, {});
    iota(indicies.begin(), indicies.end(), 0);
    for (int i = 0; i < m; ++i) {
        sort(indicies.begin(), indicies.end(), [&i](int l, int r) {
            return a[l][i] < a[r][i];
        });
        for (int j = 0; j < n - 1; ++j) {
            int index_first = m * indicies[j] + i;
            int index_second = m * indicies[j + 1] + i;
            g[index_first].push_back(index_second);
            gT[index_second].push_back(index_first);
            if (a[indicies[j]][i] == a[indicies[j + 1]][i]) {
                g[index_second].push_back(index_first);
                gT[index_first].push_back(index_second);
            }
        }
    }
    a.clear();
    comp.assign(n * m, {});
    used.assign(n * m, {});
    for (int i = 0; i < n * m; ++i) {
        if (!used[i]) {
            get_topsort(i);
        }
    }
    reverse(topsort.begin(), topsort.end());
    used.assign(n * m, {});
    for (int i : topsort) {
        if (!used[i]) {
            int col = color_timer++;
            color(i, col);
        }
    }
    used.assign(n * m, {});
    g_comp.assign(color_timer, {});
    gT_comp.assign(color_timer, {});
    for (int i = 0; i < n * m; ++i) {
        if (!used[i]) {
            condense(i);
        }
    }
    answer_for_comp.assign(color_timer, {});
    for (int i = 1; i < color_timer; ++i) {
        int mx = 0;
        for (int j : gT_comp[i]) {
            mx = max(mx, answer_for_comp[j]);
        }
        answer_for_comp[i] = mx + 1;
    }
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            cout << answer_for_comp[comp[i * m + j]] << ' ';
        }
        cout << '\n';
    }
}

signed main() {
# ifndef SEREGA
    cin.tie(nullptr)->sync_with_stdio(false);
# endif
    solve();
}
