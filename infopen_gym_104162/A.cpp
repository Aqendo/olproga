#include "bits/stdc++.h"

using namespace std;
#define int long long
#ifdef SEREGA
#include "../debug.h"
auto freopen_input_result_ = freopen("../input.txt", "r", stdin);
// auto freopen_output_result_ = freopen("output.txt", "r", stdout);
#endif

void solve() {
    int n, k;
    cin >> n >> k;
    vector<int> a(n);
    for (int i = 0; i < n; ++i) {
        cin >> a[i];
    }
    int mn = INT_MAX, mx = INT_MIN;
    int start = 0;
    vector<int> startings;
    for (int i = 0; i < n; ++i) {
        mn = min(mn, a[i]);
        mx = max(mx, a[i]);
        if (mx - mn + 1 == i - start + 1 && mx == i + 1 && mn == start + 1) {
            startings.push_back(i - start + 1);
            start = i + 1;
            mn = INT_MAX, mx = INT_MIN;
        }
    }
    if ((int)startings.size() < k) {
        cout << "-1\n";
        return;
    }
    for (int i = 0; i < k - 1; ++i) {
        cout << startings[i] << ' ';
    }
    int result = 0;
    for (int i = k - 1; i < startings.size(); ++i) {
        result += startings[i];
    }
    cout << result << '\n';
}

signed main() {
    cin.tie(nullptr)->sync_with_stdio(false);
    solve();
}
