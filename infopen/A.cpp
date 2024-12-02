#include <bits/stdc++.h>
using namespace std;
#define int int64_t
vector<int> pos['z' - 'a' + 2];
int n, m;
string s;
void test() {
    string t;
    cin >> t;
    if (pos[t[0] - 'a'].empty()) {
        cout << -1 << '\n';
        return;
    }
    int l = 0, r = n + 1;
    while (r - l > 1) {
        int mid = (l + r) >> 1;
        int now = pos[t[0] - 'a'][0];
        bool changed = false;
        for (int i = 1; i < (int)t.size(); ++i) {
            int charr = t[i] - 'a';
            auto next_index_it = lower_bound(pos[charr].begin(), pos[charr].end(), now + mid);
            if (next_index_it == pos[charr].end()) {
                r = mid;
                changed = true;
                break;
            }
            now = *next_index_it;
        }
        if (!changed) {
            l = mid;
        }
    }
    if (l == 0) {
        cout << -1 << '\n';
    } else {
        cout << l << '\n';
    }
}
void solve() {
    cin >> n >> m;
    cin >> s;
    for (int i = 0; i < n; ++i) {
        pos[s[i] - 'a'].push_back(i);
    }
    for (int i = 0; i < m; ++i) {
        test();
    }
}

signed main() {
    cin.tie(nullptr)->sync_with_stdio(false);
    int t = 1;
    // cin >> t;
    while (t--) solve();
}