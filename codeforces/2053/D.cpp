#include <bits/stdc++.h>
using namespace std;
#define int int64_t
const int MOD = 998'244'353;
void solve() {
    int n;
    cin >> n;
    int q;
    cin >> q;
    vector<int> a(n), b(n);
    multiset<int> as, bs;
    for (int i = 0; i < n; ++i) {
        cin >> a[i];
        as.insert(a[i]);
    }
    for (int i = 0; i < n; ++i) {
        cin >> b[i];
        bs.insert(b[i]);
    }
    int answer = 1;
    for (auto it1 = as.begin(), it2 = bs.begin(); it1 != as.end(); it1++, it2++) {
        answer *= min(*it1, *it2);
        answer %= MOD;
    }
    cout << answer << ' ';
    for (int i = 0; i < q; ++i) {
        int move, x;
        cin >> move >> x;
        x--;
        if (move == 1) {
            as.extract(a[x]);
            a[x]++;
            as.insert(a[x]);
        } else {
            bs.extract(b[x]);
            b[x]++;
            bs.insert(b[x]);
        }
        answer = 1;
        for (auto it1 = as.begin(), it2 = bs.begin(); it1 != as.end(); it1++, it2++) {
            answer *= min(*it1, *it2);
            answer %= MOD;
        }
        cout << answer << ' ';
    }
    cout << '\n';
}

signed main() {
    cin.tie(nullptr)->sync_with_stdio(false);
    int t = 1;
    cin >> t;
    while (t--) solve();
}