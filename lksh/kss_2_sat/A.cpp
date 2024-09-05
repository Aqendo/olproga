#include "bits/stdc++.h"

using namespace std;

#ifdef SEREGA
auto freopen_input_result_ = freopen("../input.txt", "r", stdin);
// auto freopen_output_result_ = freopen("output.txt", "r", stdout);
#endif

vector<vector<int>> g;
vector<bool> used;
vector<int> st, tin, fup, comp;

int n, m, timer = 0, color = 0;

void dfs(int x) {
    used[x] = true;
    st.push_back(x);
    tin[x] = fup[x] = timer++;
    for (int u : g[x]) {
        if (!used[u]) {
            dfs(u);
        }
        if (!comp[u]) {
            fup[x] = min(fup[x], fup[u]);
        }
    }
    if (tin[x] == fup[x]) {
        color++;
        while (st.back() != x) {
            comp[st.back()] = color;
            st.pop_back();
        }
        comp[st.back()] = color;
        st.pop_back();
    }
}

void init() {
    g.assign(n + 1, {});
    used.assign(n + 1, {});
    tin.assign(n + 1, {});
    fup.assign(n + 1, {});
    comp.assign(n + 1, {});
}

void solve() {
    cin >> n >> m;
    init();
    for (int i = 0; i < m; ++i) {
        int a, b;
        cin >> a >> b;
        g[a].push_back(b);
    }
    for (int i = 1; i <= n; ++i) {
        if (!used[i]) {
            dfs(i);
        }
    }
    int answer = 0;
    map<pair<int, int>, int> was;
    for (int i = 1; i <= n; ++i) {
        for (int u : g[i]) {
            if (i == u) continue;
            if (comp[i] != comp[u]) {
                if (!was[{comp[i], comp[u]}]++) {
                    answer++;
                }
            }
        }
    }
    cout << answer << '\n';
}

signed main() {
    cin.tie(nullptr)->sync_with_stdio(false);
    solve();
}