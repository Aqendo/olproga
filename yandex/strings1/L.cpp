#include "bits/stdc++.h"
using namespace std;
# define int long long
# ifdef SEREGA
#include "/home/ser/olproga/debug.h"
auto freopen_input_result_ = freopen(INPUT_PATH, "r", stdin);
//  auto freopen_output_result_ = freopen("output.txt", "r", stdout);
# endif

# ifndef SEREGA
# define printf(...)
# define debug(...)
# endif

vector<int> get_pref(const string& s) {
    int n = s.size();
    vector<int> pref(n);
    for (int i = 1; i < n; ++i) {
        int cur = pref[i - 1];
        while (s[cur] != s[i] && cur > 0) {
            cur = pref[cur - 1];
        }
        if (s[i] == s[cur]) {
            pref[i] = cur + 1;
        }
    }
    return pref;
}

void solve() {
    int n, m;
    cin >> n >> m;
    string search;
    cin >> search;
    vector<int> pref = get_pref(search);
    int cur = -1;
    vector<int> occurences;
    int s = 0;
    for (int i = 0; i < m; ++i) {
        printf("%lld: %lld\n", i, cur);
        if (cur == n - 1) {
            printf("OCCURENCE: %lld\n", i - search.size());
            s += i - search.size();
        }
        char c;
        cin >> c;
        if (cur == -1) {
            if (search[0] == c) {
                cur = 0;
            }
            continue;
        }
        if (cur + 1 < n && c == search[cur + 1]) {
            cur++;
            continue;
        }
        cur = pref[cur];
        while (search[cur] != c && cur > 0) {
            debug(cur, search[cur]);
            cur = pref[cur - 1];
        }
        debug(cur);
        if (c != search[cur]) {
            cur = -1;
        }
    }
    if (cur == n - 1) {
        printf("OCCURENCE: %lld\n", m - search.size());
        s += m - search.size();
    }
    cout << s << endl;
}

signed main() {
# ifndef SEREGA
    cin.tie(nullptr)->sync_with_stdio(false);
# endif
    solve();
}
