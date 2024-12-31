#include <bits/stdc++.h>
#define int int64_t
using namespace std;
void solve() {
    int n, a;
    cin >> n >> a;
    vector<int> arr(n);
    int mn = INT_MAX;
    for (int i = 0; i < n; ++i) {
        cin >> arr[i];
        mn = min(mn, arr[i]);
    }
    vector<int> p(n);
    iota(p.begin(), p.end(), 0);
    long long answer = 0;
    do {
        long long s = 0;
        for (int i = 0; i < n - 1; ++i) {
            s += arr[p[i]] % arr[p[i + 1]];
        }
        answer += s <= mn + a;
    } while (next_permutation(p.begin(), p.end()));
    cout << answer % ((int)1e9 + 7) << endl;
}

signed main() {
    cin.tie(nullptr)->sync_with_stdio(false);
    int t = 1;
    // cin >> t;
    while (t--) solve();
}