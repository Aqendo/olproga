#include "bits/stdc++.h"

using namespace std;

constexpr int MAXN = 1'000'001;

vector<int> g[MAXN];
int g_colors[MAXN];
int answer[MAXN];

set<int> dfs(int x, int p = -1) {
    set<int> answer_set;
    for (int u : g[x]) {
        if (u != p) {
            set<int> child = dfs(u, x);
            if (child.size() > answer_set.size()) swap(child, answer_set);
            answer_set.insert(child.begin(), child.end());
        }
    }
    answer_set.insert(g_colors[x]);
    answer[x] = (int)answer_set.size();
    return answer_set;
}

void solve() {
    int n;
    cin >> n;
    int root = -1;
    for (int i = 1; i <= n; ++i) {
        int p, color;
        cin >> p >> color;
        if (p == 0) {
            root = i;
        } else {
            g[i].push_back(p);
            g[p].push_back(i);
        }
        g_colors[i] = color;
    }
    dfs(root, 0);
    for (int i = 1; i <= n; ++i) {
        cout << answer[i] << ' ';
    }
}

int main() {
    cin.tie(nullptr)->sync_with_stdio(false);
    solve();
}