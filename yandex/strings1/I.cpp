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

vector<int> get_z(const string& s) {
    int n = s.size();
    vector<int> z(n);
    z[0] = n;
    int l = 0, r = 0;
    for (int i = 1; i < n; ++i) {
        if (i <= r) {
            z[i] = min(r - i + 1, z[i - l]);
        }
        while (i + z[i] < n && s[i + z[i]] == s[z[i]]) {
            z[i]++;
        }
        if (i + z[i] - 1 > r) {
            l = i;
            r = i + z[i] - 1;
        }
    }
    return z;
}

const int MAXN = 1e7;

int indicies_a[MAXN];

void solve() {
    int n, m;
    cin >> n >> m;
    if (m == 1) {
        for (int i = 1; i <= n; ++i) {
            cout << i << ' ';
        }
        return;
    }
    vector<int> a(n), b(m);
    for (int &i : a) {
        cin >> i;
    }
    for (int &i : b) {
        cin >> i;
    }
    vector<int> diff_a(n - 1), diff_b(m - 1);
    for (int i = 1; i < n; ++i) {
        diff_a[i - 1] = a[i] - a[i - 1];
    }
    for (int i = 1; i < m; ++i) {
        diff_b[i - 1] = b[i] - b[i - 1];
    }

    string s_a;
    for (int i = 0; i < (int)diff_a.size(); ++i) {
        indicies_a[s_a.size()] = i + 1;
        s_a += to_string(diff_a[i]) + "|";
    }
    string s_b;
    for (int i = 0; i < (int)diff_b.size(); ++i) {
        s_b += to_string(diff_b[i]) + "|";
    }
    string s = s_b + "#" + s_a;
    vector<int> z = get_z(s);
    for (size_t i = s_b.size(); i < s.size(); ++i) {
        if (z[i] == (int)s_b.size()) {
            cout << indicies_a[(int)i - (int)s_b.size() - 1] << ' ';
        }
    }
}

signed main() {
# ifndef SEREGA
    cin.tie(nullptr)->sync_with_stdio(false);
# endif
    solve();
}
