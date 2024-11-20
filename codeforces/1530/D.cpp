#include <bits/stdc++.h>
using namespace std;
#define int int64_t

void solve() {
    int n;
    cin >> n;
    vector<int> a(n);
    vector<int> cnt(n + 1);
    set<int> extra;
    for (int i = 1; i <= n; ++i) {
        extra.insert(i);
    }
    for (int i = 0; i < n; ++i) {
        cin >> a[i];
        extra.erase(a[i]);
        cnt[a[i]]++;
    }
    vector<int> remain_to_choose_for;
    vector<bool> should_delete(n + 1);
    for (int i = 0; i < n; ++i) {
        if (cnt[a[i]] > 1) {
            if (extra.contains(i + 1)) {
                cnt[a[i]]--;
                should_delete[a[i]] = 1;
            } else {
            }
        }
    }
}

signed main() {
    cin.tie(nullptr)->sync_with_stdio(false);
    int t;
    cin >> t;
    while (t--) solve();
}