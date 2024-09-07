#include "bits/stdc++.h"

using namespace std;
#define int long long
#ifdef SEREGA
#include "../debug.h"
auto freopen_input_result_ = freopen("../input.txt", "r", stdin);
// auto freopen_output_result_ = freopen("output.txt", "r", stdout);
#endif

void solve() {
    int a, b, c;
    cin >> a >> b >> c;
    int answer = 0;
    if (b - 2 >= 0 && c - 1 >= 0) {
        int cnt = min(b / 2, c);
        answer += cnt;
        b -= cnt * 2;
        c -= cnt;
    }
    if (b - 2 >= 0 && a - 2 >= 0) {
        int cnt = min(b / 2, a / 2);
        answer += cnt;
        a -= cnt * 2;
        b -= cnt * 2;
    }
    if (c - 2 >= 0 && a - 1 >= 0) {
        int cnt = min(c / 2, a);
        answer += cnt;
        c -= cnt * 2;
        a -= cnt;
    }
    if (a - 3 >= 0 && c - 1 >= 0) {
        int cnt = min(a / 3, c);
        answer += cnt;
        a -= cnt * 3;
        c -= cnt;
    }
    if (a - 5 >= 0) {
        int cnt = a / 5;
        answer += cnt;
        a -= cnt * 5;
    }
    cout << answer << '\n';
}

signed main() {
    cin.tie(nullptr)->sync_with_stdio(false);
    int t;
    cin >> t;
    while (t--) solve();
}
