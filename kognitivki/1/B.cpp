#include "bits/stdc++.h"
using namespace std;
#define int int64_t

void solve() {
    int n;
    cin >> n;
    vector<int> a(2 * n), b(2 * n);
    for (int i = 0; i < 2 * n; ++i) {
        cin >> a[i];
    }
    for (int i = 0; i < 2 * n; ++i) {
        cin >> b[i];
    }
    vector<int> first, second;
    for (int i = 0; i < n * 2; ++i) {
        if (a[i] < b[i]) {
            first.push_back(i);
        } else {
            second.push_back(i);
        }
    }
    if ((int)first.size() == n) {
        int answer = 0;
        for (int i : first) answer += a[i];
        for (int i : second) answer += b[i];
        cout << answer << endl;
        return;
    }
    if (first.size() > second.size()) {
        swap(a, b);
        swap(first, second);
    }
    sort(second.rbegin(), second.rend(), [&](int i, int j) { return (a[i] - b[i]) < (a[j] - b[j]); });
    int delta = (int)second.size() - n;
    for (int i = 0; i < delta; ++i) {
        first.push_back(second.back());
        second.pop_back();
    }
    int answer = 0;
    for (int i : first) answer += a[i];
    for (int i : second) answer += b[i];
    cout << answer << endl;
}

signed main() {
    cin.tie(nullptr)->sync_with_stdio(false);
    int t;
    cin >> t;
    while (t--) solve();
}
