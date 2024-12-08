#include <bits/stdc++.h>
using namespace std;

vector<vector<int>> g;

int main() {
    int n, m;
    cin >> n >> m;
    g.resize(n + 1);
    for (int i = 0; i < m; ++i) {
        int a, b;
        cin >> a >> b;
        g[a].push_back(b);
        g[b].push_back(a);
    }
    vector<vector<int>> dist(n + 1, vector<int>(2, -3));
    vector<vector<int>> par(n + 1, vector<int>(2));
    dist[1][0] = 3 * n + 1;
    priority_queue<array<int, 3>, vector<array<int, 3>>, less<>> pq;
    pq.push({3 * n + 1, 0, 1});
    while (!pq.empty()) {
        auto [remain, dist_now, v] = pq.top();
        pq.pop();
        if (remain <= 0 || dist[v][dist_now] > remain) continue;
        for (int u : g[v]) {
            if (dist[u][1 - dist_now] < remain - 1) {
                dist[u][1 - dist_now] = remain - 1;
                par[u][1 - dist_now] = v;
                pq.push({remain - 1, 1 - dist_now, u});
            }
        }
    }
    int dist_now = 1;
    if (dist[n][0] >= 0) {
        dist_now = 0;
    }
    cout << dist_now << ' ';
    int now = n;
    vector<int> path = {n};
    while (now != 1 || dist_now != 0) {
        path.push_back(par[now][dist_now]);
        now = par[now][dist_now];
        dist_now = 1 - dist_now;
    }
    reverse(path.begin(), path.end());
    cout << path.size() << '\n';
    for (int i = 0; i < (int)path.size() - 1; ++i) {
        cout << path[i] << ' ' << "+-"[i % 2] << ' ';
    }
    if (path.size()) cout << path.back() << endl;
}