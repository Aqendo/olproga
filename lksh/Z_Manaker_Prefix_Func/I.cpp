#include "bits/stdc++.h"

using namespace std;

#ifdef SEREGA
#include "../debug.h"
auto freopen_input_result_ = freopen("../input.txt", "r", stdin);
// auto freopen_output_result_ = freopen("output.txt", "r", stdout);
#endif

vector<int> z_func(const string& s) {
    // debug(s);
    vector<int> z(s.size());
    int l = 0, r = 0;
    int n = s.size();
    for (int i = 1; i < n; ++i) {
        z[i] = min(max(0, r - i), z[i - l]);
        while (i + z[i] < n && s[z[i]] == s[i + z[i]]) {
            z[i]++;
        }
        if (i + z[i] > r) {
            r = i + z[i];
            l = i;
        }
    }
    return z;
}

void solve() {
    string t, s;
    cin >> t >> s;
    if (t.size() > s.size()) {
        cout << 0 << '\n';
        return;
    }
    vector<int> normal = z_func(t + '#' + s);
    reverse(t.begin(), t.end());
    reverse(s.begin(), s.end());
    vector<int> reversed = z_func(t + '#' + s);
    reverse(t.begin(), t.end());
    reverse(s.begin(), s.end());
    size_t offset = (int)t.size() + 1;
    long long ans = 0;
    vector<int> answer;
    for (size_t i = 0; i < s.size() - t.size() + 1; ++i) {
        int result = normal[i + offset];
        if (result == t.size()) {
            answer.push_back(i + 1);
            continue;
        }
        int remain = (int)t.size() - result - 1;
        size_t index_reverse = s.size() - (i + t.size() - 1) - 1;
        int result2 = reversed[offset + index_reverse];
        if (result2 + result == t.size() || result2 + result + 1 == t.size()) {
            answer.push_back(i + 1);
        }
    }
    cout << answer.size() << '\n';
    for (int i : answer) {
        cout << i << ' ';
    }
}

signed main() {
    cin.tie(nullptr)->sync_with_stdio(false);
    solve();
}
