#include <bits/stdc++.h>
using namespace std;
#define int int64_t

void solve() {
    int n, k;
    string s;
    cin >> n >> k >> s;
    n = s.size();
    int from_now = 0;
    int up_to = 0;
    int prev = 0;
    vector<string> strs = {};
    for (int i = 0; i < n; ++i) {
        if (s[i] >= s[0]) {
            strs.push_back(string(1, s[i]));
        } else {
            strs.back().push_back(s[i]);
        }
    }
    // for (string& ss : strs) {
    //     cout << ss << endl;
    // }
    // cout << endl;
    string result;
    string best = string(k, 'z');
    for (int i = 0; i < (int)strs.size(); ++i) {
        result += strs[i];
        string comp = result;
        while ((int)comp.size() != k) {
            if ((int)comp.size() < k) {
                comp += comp;
            } else {
                comp.pop_back();
            }
        }
        best = min(best, comp);
    }
    cout << best << endl;
}

signed main() {
    cin.tie(nullptr)->sync_with_stdio(false);
    solve();
}