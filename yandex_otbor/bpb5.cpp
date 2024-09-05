#include "bits/stdc++.h"

using namespace std;
#define int long long
#ifdef SEREGA
#include "../debug.h"
auto freopen_input_result_ = freopen("../input.txt", "r", stdin);
// auto freopen_output_result_ = freopen("output.txt", "r", stdout);
#endif

void solve() {
    string s;
    cin >> s;
    vector<int> cnt(26, 0);
    for (char c : s) {
        cnt[c - 'a']++;
    }
    int answer = 0;
    int n = s.size();
    int full = n;
    int index_from = -1;
    for (int i = 0; i < n; ++i) {
        answer += full - cnt[s[i] - 'a'];
        cnt[s[i] - 'a']--;
        full--;
    }
    cout << answer + 1 << '\n';
}

signed main() {
    cin.tie(nullptr)->sync_with_stdio(false);
    solve();
}
