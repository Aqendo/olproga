#include "bits/stdc++.h"

using namespace std;
#define int long long
#ifdef SEREGA
#include "../debug.h"
auto freopen_input_result_ = freopen("../input.txt", "r", stdin);
// auto freopen_output_result_ = freopen("output.txt", "r", stdout);
#endif

void solve() {
    int n, m, d;
    cin >> n >> m >> d;
    vector<int> a(n);
    vector<vector<int>> indicies(m + 1);
    for (int i = 0; i < n; ++i) {
        cin >> a[i];
        indicies[a[i]].push_back(i);
    }
    int ans = INT_MIN;
    for (int i = 0; i <= m; ++i) {
        int l = 0, r = 0;
        int cnt = 0;
        while (l < indicies[i].size() && r < indicies[i].size() && r >= 0 && r >= 0) {
            if (cnt <= d) {
                ans = max(ans, r - l + 1);
                r++;
                if (r < indicies[i].size()) {
                    cnt += indicies[i][r] - indicies[i][r - 1] - 1;
                }
            } else {
                l++;
                if (l < indicies[i].size()) {
                    cnt -= indicies[i][l] - indicies[i][l - 1] - 1;
                }
            }
        }
    }
    cout << ans << '\n';
}

signed main() {
    cin.tie(nullptr)->sync_with_stdio(false);
    solve();
}
