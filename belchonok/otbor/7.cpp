#include <bits/stdc++.h>
using namespace std;
#define int int64_t
auto __ittt = freopen("/home/ser/olproga/belchonok/otbor/infbel.txt", "r", stdin);
void solve() {
    int n = 2000;
    vector<int> a(n);
    for (int i = 0; i < n; ++i) {
        cin >> a[i];
    }
    vector<int> inds;
    for (int i = 1; i < n - 1; ++i) {
        if (a[i - 1] > a[i] && a[i] < a[i + 1]) {
            inds.push_back(i);
        }
    }
    int mx = INT_MIN;
    for (int i = 1; i < (int)inds.size(); ++i) {
        if (inds[i] - inds[i - 1] > mx && (a[inds[i]] & 1) != (a[inds[i - 1]] & 1)) {
            mx = inds[i] - inds[i - 1];
        }
    }
    cout << mx << endl;
}

signed main() {
    cin.tie(nullptr)->sync_with_stdio(false);
    int t = 1;
    // cin >> t;
    while (t--) solve();
}