#include "bits/stdc++.h"
using namespace std;

vector<vector<int>> g;
vector<set<int>> gT;

void solve() {
    int n;
    cin >> n;
    g.assign(n + 1, {});
    gT.assign(n + 1, {});
    set<int> indicies;
    for (int i = 1; i <= n; ++i) {
        indicies.insert(-i);
    }
    for (int i = 1; i <= n; ++i) {
        int cnt;
        cin >> cnt;
        for (int j = 0; j < cnt; ++j) {
            int t;
            cin >> t;
            gT[t].insert(i);
            g[i].push_back(t);
            indicies.extract(-t);
        }
    }
    vector<int> topsort;
    while (!indicies.empty()) {
        int v = -(*indicies.begin());
        indicies.erase(indicies.begin());
        topsort.push_back(v);
        for (int u : g[v]) {
            gT[u].extract(v);
            if (gT[u].empty()) {
                indicies.insert(-u);
            }
        }
    }
    for (int i = (int)topsort.size() - 1; i >= 0; --i) {
        cout << topsort[i] << ' ';
    }
}

int main() {
    cin.tie(nullptr)->sync_with_stdio(false);
    solve();
}
