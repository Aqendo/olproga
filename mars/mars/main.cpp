#pragma GCC optimize("O3")
#include <bits/stdc++.h>
#define int int64_t
using namespace std;
#ifdef SEREGA
#include "/home/ser/olproga/debug.h"
auto __freop = freopen("/home/ser/olproga/input.txt", "r", stdin);
#else
#define debug(...)
#endif

#define all(x) (x).begin(), (x).end()
#define rall(x) (x).rbegin(), (x).rend()

bool can(int x) {
    vector<int> colored(4321 + 1);
    int left = 4321;
    for (int i = 1; i <= n; ++i) {
        left -= i;
        if (left < 0) return false;
        if (left == 0) return i;
    }
    return false;
}

signed main() {
    for (int i = 4321; i >= 1; --i) {
        if (auto cnt = can(i)) {
            cout << cnt << endl;
            return 0;
        }
    }
}
