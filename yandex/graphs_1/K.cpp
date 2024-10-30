#include "bits/stdc++.h"
using namespace std;

struct Edge {
    int u, type;
};

vector<vector<Edge>> g;
vector<int> comp, dp, tin, used;
vector<int> st;
vector<int> has_edge;
const int NEEDED = 1, NOT_NEEDED = 2;
int timer = 1;
int next_color = 1;
int n, m;

void color(int x) {
    used[x] = 1;
    tin[x] = dp[x] = timer++;
    st.push_back(x);
    for (auto& [u, type] : g[x]) {
        if (type == NEEDED) continue;
        if (!used[u]) {
            color(u);
        }
        if (!comp[u]) {
            dp[x] = min(dp[x], dp[u]);
        }
    }
    if (tin[x] == dp[x]) {
        int col = next_color++;
        while (st.back() != x) {
            comp[st.back()] = col;
            st.pop_back();
        }
        comp[st.back()] = col;
        st.pop_back();
    }
}

void get_edge(int x) {
    used[x] = 1;
    for (auto& [u, type] : g[x]) {
        if (type == NEEDED) continue;
        if (comp[x] != comp[u]) {
            has_edge[comp[x]] = 1;
        }
        if (!used[u]) {
            get_edge(u);
        }
    }
}

void get_answer(int x) {
    used[x] = 1;
    if (has_edge[comp[x]]) {
        cout << "Yes\n";
        exit(0);
    }
    for (auto& [u, type] : g[x]) {
        if (!used[u]) {
            get_answer(u);
        }
    }
}

void init() {
    g.assign(n + 1, {});
    comp.assign(n + 1, {});
    dp.assign(n + 1, {});
    tin.assign(n + 1, {});
    used.assign(n + 1, {});
}
void solve() {
    cin >> n >> m;
    init();
    for (int i = 0; i < m; ++i) {
        int a, b, type;
        cin >> a >> b >> type;
        if (a == b) continue;
        g[a].push_back({b, type});
    }
    for (int i = 1; i <= n; ++i) {
        if (!used[i]) {
            color(i);
        }
    }
    has_edge.assign(next_color, {});
    used.assign(n + 1, {});
    for (int i = 1; i <= n; ++i) {
        if (!used[i]) get_edge(i);
    }
    used.assign(n + 1, {});
    get_answer(1);
    cout << "No\n";
}

int main() {
    cin.tie(nullptr)->sync_with_stdio(false);
    solve();
}
