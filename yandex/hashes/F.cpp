#include "bits/stdc++.h"
using namespace std;
# define int int64_t
# ifdef SEREGA
# include "/home/ser/olproga/debug.h"
auto freopen_input_result_ = freopen(INPUT_PATH, "r", stdin);
//  auto freopen_output_result_ = freopen("output.txt", "r", stdout);
# endif

# ifndef SEREGA
# define printf(...)
# define debug(...)
# endif
void solve() {
    int p, q;
    cin >> p >> q;
    map<int, string> already;
    mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());
    uniform_int_distribution<int> dist(97, 122);
    vector<int> po(12);
    po[0] = 1;
    for (int i = 1; i < 12; ++i) {
        po[i] = (po[i - 1] * p) % q;
    }
    while (true) {
        string s(10, ' ');
        int h = 0;
        for (int i = 0; i < 10; ++i) {
            s[i] = dist(rng);
            h = (h * p + s[i] - 'a' + 1) % q;
        }
        if (already.find(h) != already.end()) {
            cout << already[h] << endl << s << endl;
            return;
        }
        already[h] = s;
    }
}

signed main() {
# ifndef SEREGA
    cin.tie(nullptr)->sync_with_stdio(false);
# endif
    solve();
}
