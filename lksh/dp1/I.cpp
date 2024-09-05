#include "bits/stdc++.h"

using namespace std;

#ifdef SEREGA
#include "../debug.h"
auto freopen_input_result_ = freopen("../input.txt", "r", stdin);
// auto freopen_output_result_ = freopen("output.txt", "r", stdout);
#endif

vector<int> dp;
vector<int> prev_;
vector<int8_t> is_okay;
const int INF = 1e9;

void solve() {
    int n, m;
    cin >> n >> m;
    dp.assign(1 << n, INF);
    prev_.assign(1 << n, -1);
    is_okay.assign(1 << n, false);
    vector<vector<int>> matr(1 << n, vector<int>(n));
    for (int i = 0; i < m; ++i) {
        int a, b;
        cin >> a >> b;
        a--;
        b--;
        matr[a][b] = true;
        matr[b][a] = true;
    }
    for (int mask = 0; mask < 1 << n; ++mask) {
        vector<int> children;
        children.reserve(n);
        for (int i = 0; i < n; ++i) {
            if ((mask >> i) & 1) {
                children.push_back(i);
            }
        }
        bool found = false;
        for (int i = 0; i < (int)children.size() - 1; ++i) {
            for (int j = i + 1; j < children.size(); ++j) {
                if (matr[children[i]][children[j]]) {
                    found = true;
                    break;
                }
            }
            if (found) break;
        }
        if (found) continue;
        is_okay[mask] = true;
    }
    dp[0] = 0;
    for (int mask = 0; mask < 1 << n; ++mask) {
        for (int submask = mask; submask > 0; submask = (submask - 1) & mask) {
            if (!is_okay[submask]) continue;
            if (dp[submask ^ mask] + 1 < dp[mask]) {
                prev_[mask] = submask;
                dp[mask] = dp[submask ^ mask] + 1;
            }
        }
    }
    cout << dp[(1 << n) - 1] << '\n';
    int mask = (1 << n) - 1;
    vector<int> answer(n);
    int color = 0;
    while (prev_[mask] != -1) {
        color++;
        int submask = prev_[mask];
        for (int i = 0; i < n; ++i) {
            if (submask >> i & 1) {
                answer[i] = color;
            }
        }
        mask = mask ^ submask;
    }
    for (int i : answer) {
        cout << i << ' ';
    }
    cout << '\n';
}

signed main() {
    cin.tie(nullptr)->sync_with_stdio(false);
    int t;
    cin >> t;
    while (t--) {
        solve();
    }
}
