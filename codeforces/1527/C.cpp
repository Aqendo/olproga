#include <bits/stdc++.h>
using namespace std;
#define int int64_t
void solve() {
    int n;
    cin >> n;
    map<int, int> cnt;
    int answer = 0;
    for (int i = 0; i < n; ++i) {
        int t;
        cin >> t;
        answer += cnt[t] * (n - i);
        cnt[t] += i + 1;
    }
    cout << answer << endl;
}
signed main() {
    cin.tie(nullptr)->sync_with_stdio(false);
    int t;
    cin >> t;
    while (t--) solve();
}