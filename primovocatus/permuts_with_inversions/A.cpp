#include "bits/stdc++.h"
using namespace std;
# ifdef SEREGA
# include "/home/ser/olproga/debug.h"
auto freopen_input_result_ = freopen(INPUT_PATH, "r", stdin);
//  auto freopen_output_result_ = freopen("output.txt", "r", stdout);
# endif

# ifndef SEREGA
# define printf(...)
# define debug(...)
# endif

bool try_from_i(vector<int> a, int i_) {
    int n = a.size();
    for (int i = i_; i < n; ++i) {
        a[i] = n - a[i] - 1;
    }
    vector<bool> cnt(n);
    for (int i : a) {
        cnt[i - 1] = 1;
    }
    return find(cnt.begin(), cnt.end(), 0) == cnt.end();
}

bool solve() {
    int n; cin >> n;
    int L, R;
    cin >> L >> R;
    vector<int> orig(n), revert(n);
    for (int &i : orig) cin >> i;
    map<int, int> cnt;
    for (int &i : revert) {
        cin >> i;
        cnt[i]++;
    }
    for (int i = 0; i < n; ++i) {
        if (cnt[revert[i]] == 1) {
            bool res = try_from_i(revert, i);
            if (res) return true;
            else break;
        }
        cnt[revert[i]]--;
    }
    int l = 0, r = n - 1;
    while (true) {
        
    }
    return false;
}

signed main() {
# ifndef SEREGA
    cin.tie(nullptr)->sync_with_stdio(false);
# endif
    int t; cin >> t;
    for (int i = 1; i <= t; ++i) {
        bool res = solve();
        cout << "test #" << i << (res ? " succeded\n" : " failed\n");
    }
}
