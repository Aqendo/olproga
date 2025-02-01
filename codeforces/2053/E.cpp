#include <bits/stdc++.h>
using namespace std;
#define int int64_t

vector<vector<int>> g;

vector<int> isSafe, isNearLeaf, dpDown;

int answer = 0;

bool isLeaf(int x) {
    return g[x].size() == 1;
}

void getSafe(int x, int p) {
    for (int u : g[x]) {
        if (p != u) getSafe(u, x);
    }
    if (isLeaf(x)) {
        isSafe[x] = false;
        return;
    }
    isSafe[x] = true;
    for (int u : g[x]) {
        if (isLeaf(u)) {
            isSafe[x] = false;
            return;
        }
    }
}

void getNearLeaf(int x, int p) {
    for (int u : g[x]) {
        if (u != p) getNearLeaf(u, x);
    }
    if (isLeaf(x)) {
        isNearLeaf[x] = false;
        return;
    }
    isNearLeaf[x] = false;
    for (int u : g[x]) {
        isNearLeaf[x] |= isLeaf(u);
    }
}

void getDpDown(int x, int p) {
    for (int u : g[x]) {
        if (u != p) {
            getDpDown(u, x);
            dpDown[x] += dpDown[u];
        }
    }
    dpDown[x] += isSafe[x];
}

void getAnswer(int x, int p, int up) {
    for (int u : g[x]) {
        if (!isLeaf(x) && isNearLeaf[u]) {
            if (u == p) {
                answer += up;
            } else {
                answer += dpDown[u];
            }
        }
        if (u != p) {
            getAnswer(u, x, up + dpDown[x] - dpDown[u]);
        }
    }
}

void solve() {
    int n;
    cin >> n;

    answer = 0;

    g.assign(n + 1, {});
    isSafe.assign(n + 1, {});
    isNearLeaf.assign(n + 1, {});
    dpDown.assign(n + 1, {});

    for (int i = 0; i < n - 1; ++i) {
        int a, b;
        cin >> a >> b;
        g[a].push_back(b);
        g[b].push_back(a);
    }

    getSafe(1, -1);
    getNearLeaf(1, -1);
    getDpDown(1, -1);
    getAnswer(1, -1, 0);

    int leaves = 0;
    for (int i = 1; i <= n; ++i) {
        leaves += isLeaf(i);
    }

    answer += leaves * (n - leaves);

    cout << answer << '\n';
}

signed main() {
    cin.tie(nullptr)->sync_with_stdio(false);
    int t = 1;
    cin >> t;
    while (t--) solve();
}