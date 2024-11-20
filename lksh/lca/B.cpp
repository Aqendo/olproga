#include "bits/stdc++.h"

using namespace std;

constexpr int MAXN = 100000 + 2;
constexpr int MAXM = 20000000 + 3;
vector<int> g[MAXN];
int tin[MAXN];
int a[MAXM];

struct Node {
    int x, depth;
    Node(int x_, int depth_) : x(x_), depth(depth_) {}
    Node() = default;
    bool operator<(const Node& rhs) const { return depth < rhs.depth; }
    bool operator>(const Node& rhs) const { return depth > rhs.depth; }
};

vector<Node> eulers;
vector<vector<Node>> sparse;

void dfs(int x, int depth, int p = -1) {
    eulers.emplace_back(x, depth);
    tin[x] = (int)eulers.size() - 1;
    for (int u : g[x]) {
        if (u != p) {
            dfs(u, depth + 1, x);
            eulers.emplace_back(x, depth);
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

    dfs(0, 0);

    int sz = (int)eulers.size();
    sparse.assign(__lg(sz) + 1, vector<Node>(sz));
    sparse[0] = eulers;
    for (int power = 1; power <= __lg(sz); ++power) {
        for (int i = 0; i < sz; ++i) {
            sparse[power][i] = sparse[power - 1][i];
            int index = i + (1 << (power - 1));
            if (index < sz) {
                sparse[power][i] = min(sparse[power][i], sparse[power - 1][index]);
            }
        }
    }

    function<int(int, int)> get_min = [](int l, int r) {
        int power = __lg(r - l + 1);
        Node res = sparse[power][l];
        int index = r - (1 << power) + 1;
        if (index < sparse[0].size()) {
            res = min(res, sparse[power][index]);
        }
        return res.x;
    };

    function<int(int, int)> get_lca = [&get_min](int l, int r) { return get_min(min(tin[l], tin[r]), max(tin[l], tin[r])); };

    long long x, y, z;
    cin >> a[1] >> a[2];
    cin >> x >> y >> z;
    for (int i = 3; i <= 2 * m; ++i) {
        a[i] = (x * a[i - 2] + y * a[i - 1] + z) % n;
    }

    long long prev_answer = get_lca(a[1], a[2]);
    long long sum_answer = prev_answer;

    for (int i = 2; i <= m; ++i) {
        long long first = (a[2 * i - 1] + prev_answer) % n;
        long long second = a[2 * i];
        prev_answer = get_lca(first, second);
        sum_answer += prev_answer;
    }
    cout << sum_answer << '\n';
}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    solve();
    return 0;
}