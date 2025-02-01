#include <bits/stdc++.h>
using namespace std;
#define int int64_t

void solve() {
    int n;
    cin >> n;
    string s;
    cin >> s;
    if (s.size() & 1) {
        cout << "-1\n";
        return;
    }
    vector<int> cnt(26);
    for (int i = 0; i < n; ++i) {
        cnt[s[i] - 'a']++;
        if (cnt[s[i] - 'a'] > n / 2) {
            cout << "-1\n";
            return;
        }
    }
    cnt.assign(26, 0);
    for (int i = 0; i < n / 2; ++i) {
        if (s[i] == s[n - 1 - i]) {
            cnt[s[i] - 'a']++;
        }
    }
    multiset<pair<int, int>> same;
    for (int i = 0; i < 26; ++i) {
        if (cnt[i]) same.insert({cnt[i], i});
    }
    int answer = 0;
    while (same.size() > 1) {
        auto [first1, second1] = *same.begin();
        auto [first2, second2] = *same.rbegin();
        same.erase(same.begin());
        same.erase(--same.end());
        answer += 1;
        first1--;
        first2--;
        if (first1) {
            same.insert({first1, second1});
        }
        if (first2) {
            same.insert({first2, second2});
        }
    }
    if (!same.empty()) {
        answer += same.begin()->first;
    }
    cout << answer << '\n';
}

signed main() {
    cin.tie(nullptr)->sync_with_stdio(false);
    int t = 1;
    cin >> t;
    while (t--) solve();
}