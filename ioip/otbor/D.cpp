#include <bits/stdc++.h>
using namespace std;
#define int int64_t

const int N = 2e5 + 78;
vector<vector<int>> g;
int c[N];
map<int, int> change;
map<pair<int, int>, int> cnt;
mt19937 rng(42);
#define uid(x, y) uniform_int_distribution<int>(x, y)(rng)

struct Hash {
    int su;
    int xo;
    void update(const Hash &r) {
        su += r.su;
        xo ^= r.xo;
    }
};

Hash dfs(int x, int p = -1) {
    Hash hash = {change[c[x]], change[c[x]]};
    for (int u : g[x]) {
        if (u != p) {
            hash.update(dfs(u, x));
        }
    }
    cnt[{hash.su, hash.xo}]++;
    return hash;
}
const int MOD = 1e9 + 7;
void solve() {
    int n;
    cin >> n;
    change.clear();
    g.assign(n + 1, {});
    for (int i = 1; i <= n; ++i) {
        cin >> c[i];
        if (change.find(c[i]) == change.end()) {
            change[c[i]] = uid(int(1e6), int(1e10));
        }
    }
    for (int i = 0; i < n - 1; ++i) {
        int a, b;
        cin >> a >> b;
        g[a].push_back(b);
        g[b].push_back(a);
    }
    int q;
    cin >> q;
    for (int i = 0; i < q; ++i) {
        int root;
        cin >> root;
        cnt.clear();
        dfs(root);
        int answer = 0;
        for (auto &[u, v] : cnt) {
            answer += (v * (v - 1)) / 2;
            answer %= MOD;
        }
        cout << answer << '\n';
    }
}

signed main() {
    cin.tie(nullptr)->sync_with_stdio(false);
    int t = 1;
    cin >> t;
    while (t--) solve();
}
