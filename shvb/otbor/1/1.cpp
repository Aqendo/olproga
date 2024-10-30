#ifndef SEREGA
#pragma GCC optimize("O3")
#endif
#include <bits/stdc++.h>
using namespace std;
#define int int64_t
#define all(x) (x).begin(), (x).end()

void solve() {
    int k;
    cin >> k;
    int n;
    cin >> n;
    map<string, int> cnt;
    for (int i = 0; i < n; ++i) {
        string s;
        cin >> s;
        cnt[s]++;
    }
    bool any = false;
    for (auto it = cnt.begin(); it != cnt.end(); ++it) {
        const string& str = it->first;
        const int cnt_ = it->second;
        if (cnt_ >= k / 4) {
            cout << str << '\n';
            any = true;
        }
    }
    if (!any) {
        cout << "NO\n";
    }
}

int32_t main() {
    cin.tie(nullptr)->sync_with_stdio(false);
    solve();
}