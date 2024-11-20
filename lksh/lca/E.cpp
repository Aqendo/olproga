#include "bits/stdc++.h"

using namespace std;

constexpr int MAXN = 1000000 + 3;
constexpr int MAXM = 10000000 + 3;
vector<int> g[MAXN];
vector<pair<int, int>> q[MAXN];
int parent[MAXN];
int answer[MAXM];
bool used[MAXN];

int get(int x) {
    if (x == parent[x]) return x;
    return parent[x] = get(parent[x]);
}

void unite(int a, int new_ancestor) {
    a = get(a);
    parent[a] = new_ancestor;
}

void dfs(int x, int p = -1) {
    used[x] = true;
    for (int u : g[x]) {
        if (u != p) {
            dfs(u, x);
            unite(u, x);
        }
    }
    for (auto [u, index] : q[x]) {
        if (used[u]) {
            answer[index] = get(u);
        }
    }
}

void solve() {
    int n, m;
    cin >> n >> m;
    for (int i = 1; i <= n - 1; ++i) {
        int p;
        cin >> p;
        g[p].push_back(i);
        g[i].push_back(p);
    }

    long long x, y, z;
    long long first, second;
    cin >> first >> second;
    q[first].emplace_back((int)second, 1);
    q[second].emplace_back((int)first, 1);
    cin >> x >> y >> z;
    long long sum_answer = 0;
    for (int i = 2; i <= m; ++i) {
        first = (x * first + y * second + z) % n;
        second = (x * second + y * first + z) % n;
        q[first].emplace_back((int)second, i);
        q[second].emplace_back((int)first, i);
    }

    dfs(0, 0);

    for (int i = 1; i <= m; ++i) {
        sum_answer += answer[i];
    }
    cout << sum_answer << '\n';
}

signed main() {
    for (int i = 0; i < MAXN; ++i) {
        parent[i] = i;
    }
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    solve();
}