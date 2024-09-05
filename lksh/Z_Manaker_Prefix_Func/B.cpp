#include <string>
#include "bits/stdc++.h"

using namespace std;

#ifdef SEREGA
#include "../debug.h"
auto freopen_input_result_ = freopen("../input.txt", "r", stdin);
// auto freopen_output_result_ = freopen("output.txt", "r", stdout);
#endif

void solve() {
    int n;
    cin >> n;
    string s;
    cin >> s;
    string s1 = s;
    reverse(s1.begin(), s1.end());
    s += s1;
    vector<int> z_func(n + n);
    int l = 0, r = 0;
    for (int i = 1; i < n + n; ++i) {
        if (i <= r) {
            z_func[i] = min(r - i + 1, z_func[i - l]);
        }
        while (i + z_func[i] < n + n && s[z_func[i]] == s[i + z_func[i]]) {
            z_func[i]++;
        }
        if (i + z_func[i] - 1 > r) {
            l = i;
            r = i + z_func[i] - 1;
        }
    }
    int index = 0;
    for (int i = 2 * n - 1; i >= n; --i) {
        cout << min(z_func[i], index + 1) << ' ';
        index++;
    }
}

signed main() {
    cin.tie(nullptr)->sync_with_stdio(false);
    solve();
}
