#include <bits/stdc++.h>
using namespace std;
#define int int64_t

const int N = 1e7 + 1;

int is_composite[N];
vector<int> primes;

void solve() {
    int k, n;
    cin >> k >> n;
    if (k > n * n || k > 664579) {
        cout << -1 << '\n';
        return;
    }
    for (int i = 2; i < N; ++i) {
        if (!is_composite[i]) {
            primes.push_back(i);
            for (int j = i * i; j < N; j += i) {
                is_composite[j] = true;
            }
        }
    }
    if (k <= n) {
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < n; ++j) {
                cout << primes[(i + j) % k] << ' ';
            }
            cout << '\n';
        }
    } else {
        int offset = 0;
        vector<map<int, int>> was(n);
        vector<map<int, int>> wasst(n);

        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < n; ++j) {
                int timer = 0;
                while (was[j][(i * n + offset + j) % k] || wasst[i][(i * n + offset + j) % k]) {
                    offset++;
                    timer++;
                    if (timer == k + 1) {
                        cout << -1 << '\n';
                        return;
                    }
                }
                cout << primes[(i * n + j + offset) % k] << ' ';
                was[j][(i * n + j + offset) % k] = 1;
                wasst[i][(i * n + j + offset) % k] = 1;
            }
            cout << '\n';
        }
    }
}

signed main() {
    cin.tie(nullptr)->sync_with_stdio(false);
    int t = 1;
    // cin >> t;
    while (t--) solve();
}