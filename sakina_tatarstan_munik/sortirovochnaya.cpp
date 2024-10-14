#ifndef SEREGA
#pragma GCC optimize("O3")
#endif
#include <bits/stdc++.h>
#define int int64_t
using namespace std;
#ifdef SEREGA
#include "/home/ser/olproga/debug.h"
auto __freop = freopen(INPUT_PATH, "r", stdin);
#else
#define debug(...)
#endif

#define all(x) (x).begin(), (x).end()
#define rall(x) (x).rbegin(), (x).rend()

map<int, vector<int>> g;

vector<int> bfs(int x, int needed) {
    if (x == needed) return {x};
    queue<pair<int, vector<int>>> q;
    q.push({x, {x}});
    map<int, bool> used;
    used[x] = true;
    while (!q.empty()) {
        auto [v, arr] = q.front();
        q.pop();
        for (int u : g[v]) {
            if (!used[u]) {
                arr.push_back(u);
                if (u == needed) return arr;
                used[u] = true;
                q.push({u, arr});
                arr.pop_back();
            }
        }
    }
    return {-1};
}

void solve() {
    int n; cin >> n;
    vector<int> d(n);
    map<int, int> indicies;
    for (int i = 0; i < n; ++i) {
            cin >> d[i];
            indicies[d[i]] = i;
    }
    for (int i = 0; i < n; ++i) {
        for (int j = i + 1; j < n; ++j) {
            if (d[i] % d[j] == 0 || d[j] % d[i] == 0) {
                g[d[i]].push_back(d[j]);
                g[d[j]].push_back(d[i]);
            }
        }
    }
    vector<int> needed = d;
    sort(all(needed));
    vector<int> current = d;
    vector<pair<int, int>> answer;
    for (int i = 0; i < n; ++i) {
        int from = needed[i];
        int now = current[i];
        /*
        [res]: {2}
        [res]: {12, 36, 18}
        [res]: {18, 36}
        [res]: {-1}
        */
        vector<int> path;
        vector<int> res = bfs(from, now);
        if (res[0] == -1) {
            cout << -1 << endl;
            return;
        }
        if (res.size() == 1) continue;
        debug(res);
        auto swapp = [&res, &answer, &current, &indicies](int i_, int j) {
            swap(current[indicies[res[i_]]], current[indicies[res[j]]]);
            swap(indicies[res[i_]], indicies[res[j]]);
            if (!answer.empty() && ((res[i_] == answer.back().first && res[j] == answer.back().second) || (res[j] == answer.back().first && res[i_] == answer.back().second))) {
                debug(2);
                debug(answer);
                answer.pop_back();
            } else {
                debug(22);
                answer.emplace_back(res[i_], res[j]);
                debug(answer);
            }
            swap(res[i_], res[j]);
        };

        if (res.size() == 2) {
            debug(1);
            swapp(0, 1);
            continue;
        }
        for (int j = 1; j < (int)res.size(); ++j) {
            swapp(0, j);
        }
        for (int j = (int)res.size() - 2; j > 0; --j) {
            swapp((int)res.size() - 1, j);
        }
    }
    cout << answer.size() << '\n';
    for (auto &[i, j] : answer) {
        cout << i << ' ' << j << '\n';
    }
}

signed main() {
#ifndef SEREGA
    cin.tie(nullptr)->sync_with_stdio(false);
#endif
    int t = 1;
    cerr << "STARTED" << endl;
    // cin >> t;
    while (t--) {
        solve();
    }
}
