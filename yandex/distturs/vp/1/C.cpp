#pragma GCC optimize("O3")
#include <bits/stdc++.h>
using namespace std;

const int N = 100, K = 31;
int n, k;
string a[N];
int cache[K][N][N];

int rec(int bit, int l, int r, int cnt = 0) {
    if (l > r) return cnt;
    if (bit >= k) return cnt;
    if (cache[bit][l][r] != -1) return cnt + cache[bit][l][r];
    int answer = INT_MAX;
    for (int cnt0 = l - 1; cnt0 <= r; ++cnt0) {
        int answer1 = 0;
        int answer2 = 0;

        for (int i = l; i <= r; ++i) {
            if (i <= cnt0) {
                answer1 += a[i][bit] == '1';
            } else {
                answer2 += a[i][bit] == '0';
            }
        }
        answer = min(answer, rec(bit + 1, l, cnt0, answer1) + rec(bit + 1, cnt0 + 1, r, answer2));
    }
    cache[bit][l][r] = answer;
    return cnt + answer;
}

void solve() {
    cin >> n >> k;
    for (int i = 0; i < k; ++i) {
        for (int j = 0; j < n; ++j) {
            for (int m = 0; m < n; ++m) {
                cache[i][j][m] = -1;
            }
        }
    }
    for (int i = 0; i < n; ++i) {
        cin >> a[i];
    }
    cout << rec(0, 0, n - 1, 0) << '\n';
}

signed main() {
    cin.tie(nullptr)->sync_with_stdio(false);
    int t = 1;
    cin >> t;
    while (t--) solve();
}
