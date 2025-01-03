#include <bits/stdc++.h>
using namespace std;
#define int int64_t
vector<int> needed = {-48, 256, 203, 10, 73};
vector<int> got = {0, 0, 0, 0, 0};
void dfs(int x, int left = 7) {
    for (int i = 0; i < needed.size(); ++i) {
        if (x == needed[i]) {
            got[i] = 1;
        }
    }
    if (left == 0) {
        return;
    }
    dfs(x * 2, left - 1);
    dfs(5 - x, left - 1);
    dfs(x * 3, left - 1);
}

void solve() {
    dfs(1);
    for (int i = 0; i < needed.size(); ++i) {
        cout << needed[i] << ' ' << got[i] << endl;
    }
}

signed main() {
    cin.tie(nullptr)->sync_with_stdio(false);
    int t = 1;
    // cin >> t;
    while (t--) solve();
}