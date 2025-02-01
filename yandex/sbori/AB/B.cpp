#include <bits/stdc++.h>
using namespace std;
#define int int64_t

void solvek2(int n, int k) {
    for (int i = 0; i < k - 2; ++i) {
        cout << 1 << ' ';
    }
    assert((n - (k - 2)) / 2 != 0);
    assert(k - 2 + ((n - (k - 2)) / 2 * 2) == n);
    cout << (n - (k - 2)) / 2 << ' ' << (n - (k - 2)) / 2 << '\n';
}

void solve() {
    int n, k;
    cin >> n >> k;
    if (n & 1) {
        cout << -1;
        return;
    }
    if (k > n) {
        cout << -1;
        return;
    }
    if (k % 2 == 0) {
        solvek2(n, k);
        return;
    }
    if (k > 3) {
        if (n - 6 > 0) {
            cout << "1 2 3 ";
            solvek2(n - 6, k - 3);
            return;
        }
        cout << -1 << '\n';
        return;
    }
    array<int, 3> answer = {0, 0, 0};
    int p = 1;
    for (int bit = 0; bit < 34; ++bit) {
        if (n >> (bit + 1) & 1) {
            answer[p] |= (1ll << bit);
            answer[2] |= (1ll << bit);
            p = 1 - p;
        }
    }
    if (count(answer.begin(), answer.end(), 0) != 0) {
        cout << -1 << '\n';
        return;
    }
    for (int i : answer) {
        cout << i << ' ';
    }
}

signed main() {
    cin.tie(nullptr)->sync_with_stdio(false);
    solve();
}