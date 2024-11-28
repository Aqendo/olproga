#include <bits/stdc++.h>
using namespace std;
#define int int64_t

void solve() {
    int n;
    cin >> n;
    vector<int> a(n), b;
    for (int i = 0; i < n; ++i) {
        cin >> a[i];
    }
    b = a;
    sort(b.begin(), b.end());
    map<int, int> pos_a, pos_b;
    for (int i = 0; i < n; ++i) {
        pos_a[a[i]] = i;
        pos_b[b[i]] = i;
    }
    int answer = 0;
    for (int i = n - 1; i >= 0; --i) {
        if (pos_a[b[i]] == i) continue;
        vector<int> chain = {pos_a[b[i]]};
        vector<bool> was(n, false);
        was[pos_a[b[i]]] = true;
        while (true) {
            int new_ = pos_b[a[chain.back()]];
            if (was[new_]) break;
            chain.push_back(new_);
            was[new_] = true;
        }
        answer += chain.size() * 2 + 1;
        for (int j : chain) {
            pos_a[a[j]] = pos_b[a[j]];
        }
    }
    cout << answer << endl;
}

signed main() {
    cin.tie(nullptr)->sync_with_stdio(false);
    int t = 1;
    // cin >> t;
    while (t--) solve();
}