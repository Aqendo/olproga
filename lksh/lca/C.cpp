#include "bits/stdc++.h"

using namespace std;

constexpr int MAXN = 100000 + 2;
constexpr int LIMIT_LOG = 29;
vector<vector<int>> g;
vector<int> binup[LIMIT_LOG];
vector<vector<long long>> paths;
vector<int> index_of_path_of;
vector<int> index_in_path_of;
int lgg[MAXN];

int dfs(int x, int depth, int p = 0) {
    binup[0][x] = p;
    int mx = INT_MIN;
    int index_mx = -1;
    for (int u : g[x]) {
        if (u != p) {
            int result = dfs(u, depth + 1, x);
            if (result > mx) {
                mx = result;
                index_mx = u;
            }
        }
    }
    if (g[x].size() <= 1) {
        index_of_path_of[x] = ssize(paths);
        paths.push_back({x});
    } else {
        index_of_path_of[x] = index_of_path_of[index_mx];
        paths[index_of_path_of[x]].push_back(x);
        index_in_path_of[x] = ssize(paths[index_of_path_of[x]]) - 1;
    }
    return (mx == INT_MIN ? 0 : mx) + 1;
}

void solve() {
    int n, m;
    cin >> n >> m;
    g.assign(n + 1, {});
    index_of_path_of.assign(n + 1, {});
    index_in_path_of.assign(n + 1, {});
    for (int i = 0; i < LIMIT_LOG; ++i) {
        binup[i].assign(n, {});
    }
    for (int i = 1; i <= n - 1; ++i) {
        int p;
        cin >> p;
        g[p].push_back(i);
        g[i].push_back(p);
    }

    dfs(0, 0);

    for (int power = 1; power < LIMIT_LOG; ++power) {
        for (int i = 0; i < n; ++i) {
            binup[power][i] = binup[power - 1][binup[power - 1][i]];
        }
    }
    for (auto& arr : paths) {
        int sz = (int)arr.size();
        for (int i = 0; i < sz; ++i) {
            arr.push_back(binup[0][arr.back()]);
        }
    }
    auto get_la = [&n](long long v, long long d) {
        if (d <= 0) return v;
        if (d >= n) return 0ll;
        int power = lgg[d];
        int powered = 1 << power;
        d -= powered;
        v = binup[power][v];
        if (d == 0) return v;
        if (d + index_in_path_of[v] >= paths[index_of_path_of[v]].size()) return paths[index_of_path_of[v]].back();
        return paths[index_of_path_of[v]][d + index_in_path_of[v]];
    };
    long long x, y, z;
    long long first, second;
    cin >> first >> second;
    cin >> x >> y >> z;
    long long prev_answer = get_la(first, second);
    long long sum_answer = prev_answer;
    for (int i = 2; i <= m; ++i) {
        first = (x * first + y * second + z) % n;
        second = (x * second + y * first + z) % n;
        prev_answer = get_la((first + prev_answer) % n, second);
        sum_answer += prev_answer;
    }
    cout << sum_answer << '\n';
}

signed main() {
    lgg[1] = 0;
    for (int i = 2; i < MAXN; ++i) {
        lgg[i] = lgg[i >> 1] + 1;
    }
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    solve();
}