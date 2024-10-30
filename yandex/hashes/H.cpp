#include <bits/stdc++.h>
# define int int64_t
# ifdef SEREGA
auto _freop_ = freopen("input.txt", "r", stdin);
# endif // SEREGA
using namespace std;

vector<vector<int>> g1, g2;

vector<int> h;
map<vector<int>, int> hash_by_vector;
vector<char> used;

int timer = 1;

void get_hash(int x, vector<vector<int>> &g) {
    used[x] = true;
    vector<int> children;
    for (int u : g[x]) {
        if (!used[u]) {
            get_hash(u, g);
            children.push_back(h[u]);
        }
    }
    if (children.empty()) {
        return;
    }
    sort(children.begin(), children.end());
    auto it = hash_by_vector.find(children);
    if (it != hash_by_vector.end()) {
        h[x] = it->second;
    } else {
        hash_by_vector[children] = h[x] = timer++;
    }
}

void solve() {
    int n, r1, r2;
    cin >> n >> r1 >> r2;
    g1.assign(n + 1, {});
    g2.assign(n + 1, {});
    used.assign(n + 1, {});
    for (int i = 0; i < n - 1; ++i) {
        int a, b;
        cin >> a >> b;
        g1[a].push_back(b);
        g1[b].push_back(a);
    }
    for (int i = 0; i < n - 1; ++i) {
        int a, b;
        cin >> a >> b;
        g2[a].push_back(b);
        g2[b].push_back(a);
    }
    used.assign(n + 1, {});
    h.assign(n + 1, {});
    get_hash(r1, g1);
    int hash_first = h[r1];
    used.assign(n + 1, {});
    h.assign(n + 1, {});
    timer = 1;
    get_hash(r2, g2);
    int hash_second = h[r2];
    cout << (hash_first == hash_second ? "YES" : "NO");
}

signed main() {
    cin.tie(nullptr)->sync_with_stdio(false);
    solve();
    return 0;
}
