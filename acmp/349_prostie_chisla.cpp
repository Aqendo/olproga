#include "bits/stdc++.h"
using namespace std;

const int MAXN = 1000002;
bool is_found = false;
void primes(int l, int r) {
    vector<int> p(MAXN);
    vector<int> primes;
    for (int i = 2; i < MAXN; ++i) {
        if (!p[i]) {
            p[i] = i;
            primes.push_back(i);
        }
        for (int j : primes) {
            if (1ll * i * j >= MAXN || j > p[i]) break;
            p[i * j] = j;
        }
    }
    for (int i = l; i <= r; ++i) {
        if (p[i] == i) {
            is_found = true;
            cout << i << '\n';
        }
    }
}

void solve() {
    int l, r;
    cin >> l >> r;
    primes(l, r);
    if (!is_found) {
        cout << "Absent\n";
    }
}

int main() {
    cin.tie(nullptr)->sync_with_stdio(false);
    solve();
}