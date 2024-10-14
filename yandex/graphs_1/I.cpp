#include "bits/stdc++.h"
using namespace std;
# define int long long
# ifdef SEREGA
# include "/home/ser/olproga/debug.h"
auto freopen_input_result_ = freopen(INPUT_PATH, "r", stdin);
//  auto freopen_output_result_ = freopen("output.txt", "r", stdout);
# endif

# ifndef SEREGA
# define printf(...)
# define debug(...)
# endif

vector<vector<int>> g, gT;
vector<int> a, color, used;
vector<int> topsort;
int n, m, k;

void init() {
    a.assign(n + 1, {});
    g.assign(n + 1, {});
    gT.assign(n + 1, {});
}

bool has_cycle = false;

int timer_ = 0;
void dfs(int x, int mx) {
    used[x] = 1;
    timer_++;
    if (timer_ >= 100) exit(0);
    if (has_cycle) return;
    for (int u : g[x]) {
        if (a[u] > mx) continue;
        if (!used[u]) {
            dfs(u, mx);
        }
        if (used[u] == 1) {
            has_cycle = true;
            return;
        }
    }
    used[x] = 2;
}

void get_topsort(int x, int mx) {
    used[x] = 1;
    for (int u : g[x]) {
        if (a[u] > mx) continue;
        if (!used[u]) {
            get_topsort(u, mx);
        }
    }
    topsort.push_back(x);
}

bool check(int mx) {
    used.assign(n + 1, {});
    has_cycle = false;
    for (int i = 1; i <= n; ++i) {
        if (!used[i] && a[i] <= mx) dfs(i, mx);
    }
    if (has_cycle) return true;
    topsort.clear();
    used.assign(n + 1, {});
    for (int i = 1; i <= n; ++i) {
        if (!used[i] && a[i] <= mx) get_topsort(i, mx);
    }
    reverse(topsort.begin(), topsort.end());
    vector<int> dp(n + 1);
    for (int i : topsort) {
        for (int j : gT[i]) {
            if (a[j] > mx) continue;
            dp[i] = max(dp[i], dp[j]);
        }
        dp[i]++;
        if (dp[i] >= k) return true;
    }
    return false;
}

void solve() {
    cin >> n >> m >> k;
    init();
    int mx = 0;
    for (int i = 1; i <= n; ++i) {
        cin >> a[i];
        mx = max(mx, a[i]);
    }
    for (int i = 0; i < m; ++i) {
        int a_, b;
        cin >> a_ >> b;
        g[a_].push_back(b);
        gT[b].push_back(a_);
    }
    int l = 0, r = mx + 1;
    while (r - l > 1) {
        int m_ = (l + r) >> 1;
        if (!check(m_)) {
            l = m_;
        } else {
            r = m_;
        }
    }
    if (check(r)) {
        cout << r << endl;
    } else {
        cout << -1 << endl;
    }
}

signed main() {
# ifndef SEREGA
    cin.tie(nullptr)->sync_with_stdio(false);
# endif
    solve();
}
