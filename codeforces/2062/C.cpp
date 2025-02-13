#include <bits/stdc++.h>
using namespace std;
#define int int64_t

int mx = INT_MIN;
set<vector<int>> already;
void dfs(vector<int> a) {
    if (already.contains(a)) return;
    int s = 0;
    for (int i : a) {
        s += i;
    }
    mx = max(mx, s);
    if (a.size() == 1) return;
    vector<int> todo(a.size() - 1);
    for (int i = 1; i < a.size(); ++i) {
        todo[i - 1] = a[i] - a[i - 1];
    }
    reverse(a.begin(), a.end());
    vector<int> todo2(a.size() - 1);
    for (int i = 1; i < a.size(); ++i) {
        todo2[i - 1] = a[i] - a[i - 1];
    }
    dfs(todo2);
    dfs(todo);
    already.insert(a);
}

void solve() {
    already.clear();
    int n;
    cin >> n;
    mx = INT_MIN;
    vector<int> a(n);
    for (int i = 0; i < n; ++i) {
        cin >> a[i];
    }
    dfs(a);
    cout << mx << '\n';
}

signed main() {
    cin.tie(nullptr)->sync_with_stdio(false);
    int t = 1;
    cin >> t;
    while (t--) solve();
}
