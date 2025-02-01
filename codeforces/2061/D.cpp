#include <bits/stdc++.h>
using namespace std;
#define int int64_t

map<int, int> cnt;
int used = 0;
bool has(int x) {
    if (cnt.contains(x) && cnt[x] > 0) {
        cnt[x]--;
        used++;
        return true;
    }
    if (x == 1) return false;
    return has(x / 2) && has(x - x / 2);
}
void solve() {
    int n, m;
    used = 0;
    cin >> n >> m;
    cnt.clear();
    vector<int> b(m);
    for (int i = 0; i < n; ++i) {
        int t;
        cin >> t;
        cnt[t]++;
    }
    for (int i = 0; i < m; ++i) {
        cin >> b[i];
    }
    sort(b.rbegin(), b.rend());
    for (int i : b) {
        if (!has(i)) {
            cout << "No\n";
            return;
        }
    }
    if (used != n) {
        cout << "No\n";
        return;
    }
    cout << "Yes\n";
}

signed main() {
    cin.tie(nullptr)->sync_with_stdio(false);
    int t = 1;
    cin >> t;
    while (t--) solve();
}