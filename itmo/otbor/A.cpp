#pragma GCC optimize("O3")
#include <bits/extc++.h>
#include <bits/stdc++.h>
using namespace std;
using namespace __gnu_pbds;
gp_hash_table<int, int> a;
long long answer = 0;
long long cnt = 0;
void solve() {
    long long n = -8485;
    while (n != 0) {
        cnt++;
        answer += n;
        if (cnt == 1e10) {
            cout << answer << endl;
            return;
        }
        if (n & 1) {
            n = 3 * n + 1;
        } else {
            n = n / 2;
        }
    }
    cout << cnt << endl;
}
signed main() {
    cin.tie(nullptr)->sync_with_stdio(false);
    int t = 1;
    while (t--) solve();
}