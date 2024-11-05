#include "bits/stdc++.h"
using namespace std;
vector<vector<pair<int, int>>> g;
void solve() {
    int n, m;
    cin >> n >> m;
    g.assign(n + 1, {});
    for (int i = 0; i < m; ++i) {
        int a, b, w;
        cin >> a >> b >> w;
        g[a].emplace_back(b, w);
        g[b].emplace_back(a, w);
    }
    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;
    int first = 1;
    pq.push({0, first});
    vector<int> used(n + 1, false);
    long long answer = 0;
    while (!pq.empty()) {
        auto [w, v] = pq.top();
        pq.pop();
        if (used[v]) continue;
        answer += w;
        used[v] = true;
        for (auto& [u, we] : g[v]) {
            if (!used[u]) {
                pq.push({we, u});
            }
        }
    }
    cout << answer << endl;
}

int main() {
    cin.tie(nullptr)->sync_with_stdio(false);
    solve();
}
